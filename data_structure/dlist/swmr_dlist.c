/**
 * @file swmr_dlist.c
 * @author wang.changjie (wang.changjie@embedway.com)
 * @brief 无锁队列，实际上是用两个队列实现的
 * @version 0.1
 * @date 2022-11-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "d_list.h"
#include "../tools.h"
#include "../atomic/iatomic.h"

#define CAS(_a, _o, _n)                                                        \
    ({                                                                         \
        __typeof__(_o) __o = _o;                                               \
        __asm__ __volatile__("lock cmpxchg %3,%1"                              \
                             : "=a"(__o), "=m"(*(volatile unsigned int *)(_a)) \
                             : "0"(__o), "r"(_n));                             \
        __o;                                                                   \
    })

typedef struct _Swmrd_list
{
    // 前8位表明是哪一个 dlist, 后面24位做计数用
    atomic_t rd_index_and_ref;
    d_list *dlists[2];
} Swmrd_list;

void swmr_dlist_destroy(Swmrd_list *this);

Swmrd_list *swmr_dlist_create(data_destroy_func data_destroy, void *ctx)
{
    Ret ret          = RET_FAIL;
    Swmrd_list *this = (Swmrd_list *)calloc(1, sizeof(Swmrd_list));

    do {
        if ((this->dlists[0] = dlist_create(data_destroy, ctx)) == NULL) {
            break;
        }

        if ((this->dlists[1] = dlist_create(data_destroy, ctx)) == NULL) {
            break;
        }

        ret = RET_OK;
    } while (0);

    if (ret != RET_OK) {
        swmr_dlist_destroy(this);
        this = NULL;
    }

    return this;
}

void swmr_dlist_destroy(Swmrd_list *this)
{
    if (this != NULL) {
        if (this->dlists != NULL) {
            dlist_destroy(this->dlists[0]);
            dlist_destroy(this->dlists[1]);
            this->dlists[0] = NULL;
            this->dlists[1] = NULL;
        }
        free(this);
    }

    return;
}

int swmr_dlist_find(Swmrd_list *this, data_cmp_fun cmp, void *ctx)
{
    int ret = 0;
    return_val_if_fail(this != NULL && this->dlists != NULL, -1);

    atomic_inc(&(this->rd_index_and_ref));
    size_t rd_index = (this->rd_index_and_ref.counter >> 24) & 0x1;
    ret             = dlist_find(this->dlists[rd_index], cmp, ctx);
    atomic_dec(&(this->rd_index_and_ref));

    return ret;
}

int swmr_dlist_length(Swmrd_list *this)
{
    int ret = 0;
    return_val_if_fail(this != NULL && this->dlists != NULL, -1);

    atomic_inc(&(this->rd_index_and_ref));
    size_t rd_index = (this->rd_index_and_ref.counter >> 24) & 0x1;
    ret             = dlist_length(this->dlists[rd_index]);
    atomic_dec(&(this->rd_index_and_ref));

    return ret;
}

Ret swmr_dlist_insert(Swmrd_list *this, size_t index, void *data)
{
    Ret ret          = RET_FAIL;
    d_list *wr_dlist = NULL;
    return_val_if_fail(this != NULL && this->dlists != NULL, ret);

    size_t wr_index = !((this->rd_index_and_ref.counter >> 24) & 0x1);
    if ((ret = dlist_insert(this->dlists[wr_index], index, data)) == RET_OK) {
        int rd_index_old = this->rd_index_and_ref.counter & 0xFF000000;
        int rd_index_new = wr_index << 24;

        do {
            usleep(100);
        } while (CAS(&(this->rd_index_and_ref), rd_index_old, rd_index_new));

        wr_index = rd_index_old >> 24;
        ret      = dlist_insert(this->dlists[wr_index], index, data);
    }

    return ret;
}

Ret swmr_dlist_delete(Swmrd_list *this, size_t index)
{
    Ret ret          = RET_FAIL;
    d_list *wr_dlist = NULL;
    return_val_if_fail(this != NULL && this->dlists != NULL, ret);

    size_t wr_index = !((this->rd_index_and_ref.counter >> 24) & 0x1);
    if ((ret = dlist_delete(this->dlists[wr_index], index)) == RET_OK) {
        int rd_index_old = this->rd_index_and_ref.counter & 0xFF000000;
        int rd_index_new = wr_index << 24;

        do {
            usleep(100);
        } while (CAS(&(this->rd_index_and_ref), rd_index_old, rd_index_new));

        wr_index = rd_index_old >> 24;
        ret      = dlist_delete(this->dlists[wr_index], index);
    }

    return ret;
}

#ifdef SWMR_DLIST_TEST
#include <pthread.h>
#define NR 1000
static int cmp_int(void *ctx, void *data) { return (int)data - (int)ctx; }
static void *reader(void *param)
{
    int i            = 0;
    int j            = 0;
    size_t length    = 0;
    Swmrd_list *swmr = (Swmrd_list *)param;

    for (j = 0; j < NR; j++) {
        for (i = 0; i < swmr_dlist_length(swmr); i++) {
            assert(swmr_dlist_find(swmr, cmp_int, (void *)i) == i);
        }
    }

    return NULL;
}

static void *writer(void *param)
{
    int i            = 0;
    Swmrd_list *swmr = (Swmrd_list *)param;

    for (i = 0; i < NR; i++) {
        swmr_dlist_insert(swmr, i, (void *)i);
    }

    for (; i > 0; i--) {
        swmr_dlist_delete(swmr, i);
    }

    return NULL;
}

#define RD_NR 100

int main(int argc, char *argv[])
{
    int i                    = 0;
    pthread_t wr_tid         = 0;
    pthread_t rd_tids[RD_NR] = { 0 };
    Swmrd_list *swmr         = swmr_dlist_create(NULL, NULL);

    pthread_create(&wr_tid, NULL, writer, swmr);
    for (i = 0; i < RD_NR; i++) {
        pthread_create(rd_tids + i, NULL, reader, swmr);
    }

    for (i = 0; i < RD_NR; i++) {
        pthread_join(rd_tids[i], NULL);
    }

    pthread_join(wr_tid, NULL);

    return 0;
}
#endif /*SWMR_DLIST_TEST*/
