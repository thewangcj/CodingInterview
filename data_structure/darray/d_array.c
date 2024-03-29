#include "d_array.h"
#include "../tools.h"
#include <stdio.h>
struct _d_array
{
    void **data;
    size_t size;
    size_t alloc_size;

    void *data_destroy_ctx;
    DataDestroyFunc data_destroy;
};

static void darray_destroy_data(d_array *thiz, void *data)
{
    if (thiz->data_destroy != NULL) {
        thiz->data_destroy(thiz->data_destroy_ctx, data);
    }

    return;
}

d_array *darray_create(DataDestroyFunc data_destroy, void *ctx)
{
    d_array *thiz = malloc(sizeof(d_array));

    if (thiz != NULL) {
        thiz->data             = NULL;
        thiz->size             = 0;
        thiz->alloc_size       = 0;
        thiz->data_destroy     = data_destroy;
        thiz->data_destroy_ctx = ctx;
    }

    return thiz;
}

// 这里是为了防止动态数组过于频繁的扩大或者缩小
#define MIN_PRE_ALLOCATE_NR 10
// 检查当前动态数组是否可以在放下 need 数量的元素
static Ret darray_expand(d_array *thiz, size_t need)
{
    return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);

    // 放不下了重新分配
    if ((thiz->size + need) > thiz->alloc_size) {
        // alloc_size = alloc_size_old * 1.5 + MIN_PRE_ALLOCATE_NR，这里不直接乘以 1.5 是为了避免整数溢出和乘除法运算
        // 加上 MIN_PRE_ALLOCATE_NR 是为了避免 alloc_size 为 0 的情况
        size_t alloc_size =
            thiz->alloc_size + (thiz->alloc_size >> 1) + MIN_PRE_ALLOCATE_NR;

        void **data = (void **)realloc(thiz->data, sizeof(void *) * alloc_size);
        if (data != NULL) {
            thiz->data       = data;
            thiz->alloc_size = alloc_size;
        }
    }

    return ((thiz->size + need) <= thiz->alloc_size) ? RET_OK : RET_FAIL;
}

// 当 size 小于 alloc_size 的一半时缩小数组大小节省内存空间
static Ret darray_shrink(d_array *thiz)
{
    return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);
    // 限制 alloc_size 小于 MIN_PRE_ALLOCATE_NR 是未来了避免频繁的 shrink
    if ((thiz->size < (thiz->alloc_size >> 1)) &&
        (thiz->alloc_size > MIN_PRE_ALLOCATE_NR)) {
        size_t alloc_size = thiz->size + (thiz->size >> 1);

        void **data = (void **)realloc(thiz->data, sizeof(void *) * alloc_size);
        if (data != NULL) {
            thiz->data       = data;
            thiz->alloc_size = alloc_size;
        }
    }

    return RET_OK;
}

Ret darray_insert(d_array *thiz, size_t index, void *data)
{
    Ret ret       = RET_OOM;
    size_t cursor = index;
    return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);

    cursor = cursor < thiz->size ? cursor : thiz->size;

    if (darray_expand(thiz, 1) == RET_OK) {
        size_t i = 0;
        for (i = thiz->size; i > cursor; i--) {
            thiz->data[i] = thiz->data[i - 1];
        }

        thiz->data[cursor] = data;
        thiz->size++;

        ret = RET_OK;
    }

    return ret;
}

Ret darray_prepend(d_array *thiz, void *data)
{
    return darray_insert(thiz, 0, data);
}

Ret darray_append(d_array *thiz, void *data)
{
    // index 是无符号数这里 -1 肯定非常大
    return darray_insert(thiz, -1, data);
}

Ret darray_delete(d_array *thiz, size_t index)
{
    size_t i = 0;
    Ret ret  = RET_OK;

    return_val_if_fail(thiz != NULL && thiz->size > index, RET_INVALID_PARAMS);

    darray_destroy_data(thiz, thiz->data[index]);
    for (i = index; (i + 1) < thiz->size; i++) {
        thiz->data[i] = thiz->data[i + 1];
    }
    thiz->size--;

    darray_shrink(thiz);

    return RET_OK;
}

Ret darray_get_by_index(d_array *thiz, size_t index, void **data)
{

    return_val_if_fail(thiz != NULL && data != NULL && index < thiz->size,
                       RET_INVALID_PARAMS);

    *data = thiz->data[index];

    return RET_OK;
}

Ret darray_set_by_index(d_array *thiz, size_t index, void *data)
{
    return_val_if_fail(thiz != NULL && index < thiz->size, RET_INVALID_PARAMS);

    thiz->data[index] = data;

    return RET_OK;
}

size_t darray_length(d_array *thiz)
{
    size_t length = 0;

    return_val_if_fail(thiz != NULL, 0);

    return thiz->size;
}

Ret darray_foreach(d_array *thiz, DataVisitFunc visit, void *ctx)
{
    size_t i = 0;
    Ret ret  = RET_OK;
    return_val_if_fail(thiz != NULL && visit != NULL, RET_INVALID_PARAMS);

    for (i = 0; i < thiz->size; i++) {
        ret = visit(ctx, thiz->data[i]);
    }

    return ret;
}

int darray_find(d_array *thiz, DataCompareFunc cmp, void *ctx)
{
    size_t i = 0;

    return_val_if_fail(thiz != NULL && cmp != NULL, -1);

    for (i = 0; i < thiz->size; i++) {
        if (cmp(ctx, thiz->data[i]) == 0) {
            break;
        }
    }

    return i;
}

void darray_destroy(d_array *thiz)
{
    size_t i = 0;

    if (thiz != NULL) {
        for (i = 0; i < thiz->size; i++) {
            darray_destroy_data(thiz, thiz->data[i]);
        }

        SAFE_FREE(thiz->data);
        SAFE_FREE(thiz);
    }

    return;
}

#define DARRAY_TEST
#ifdef DARRAY_TEST

#include <assert.h>

static int int_cmp(void *ctx, void *data) { return (int)data - (int)ctx; }

static Ret print_int(void *ctx, void *data)
{
    printf("%d ", (int)data);

    return RET_OK;
}

static Ret check_and_dec_int(void *ctx, void *data)
{
    int *expected = (int *)ctx;
    assert(*expected == (int)data);

    (*expected)--;

    return RET_OK;
}

static void test_int_darray(void)
{
    size_t i        = 0;
    size_t n        = 100;
    size_t data     = 0;
    d_array *darray = darray_create(NULL, NULL);

    for (i = 0; i < n; i++) {
        assert(darray_append(darray, (void *)i) == RET_OK);
        assert(darray_length(darray) == (i + 1));
        assert(darray_get_by_index(darray, i, (void **)&data) == RET_OK);
        assert(data == i);
        assert(darray_set_by_index(darray, i, (void *)(2 * i)) == RET_OK);
        assert(darray_get_by_index(darray, i, (void **)&data) == RET_OK);
        assert(data == 2 * i);
        assert(darray_set_by_index(darray, i, (void *)i) == RET_OK);
        assert(darray_find(darray, int_cmp, (void *)i) == i);
    }

    for (i = 0; i < n; i++) {
        assert(darray_get_by_index(darray, 0, (void **)&data) == RET_OK);
        assert(data == (i));
        assert(darray_length(darray) == (n - i));
        assert(darray_delete(darray, 0) == RET_OK);
        assert(darray_length(darray) == (n - i - 1));
        if ((i + 1) < n) {
            assert(darray_get_by_index(darray, 0, (void **)&data) == RET_OK);
            assert((int)data == (i + 1));
        }
    }

    assert(darray_length(darray) == 0);

    for (i = 0; i < n; i++) {
        assert(darray_prepend(darray, (void *)i) == RET_OK);
        assert(darray_length(darray) == (i + 1));
        assert(darray_get_by_index(darray, 0, (void **)&data) == RET_OK);
        assert(data == i);
        assert(darray_set_by_index(darray, 0, (void *)(2 * i)) == RET_OK);
        assert(darray_get_by_index(darray, 0, (void **)&data) == RET_OK);
        assert(data == 2 * i);
        assert(darray_set_by_index(darray, 0, (void *)i) == RET_OK);
    }

    i = n - 1;
    assert(darray_foreach(darray, check_and_dec_int, &i) == RET_OK);

    darray_destroy(darray);

    return;
}

static void test_invalid_params(void)
{
    printf("===========Warning is normal begin==============\n");
    assert(darray_length(NULL) == 0);
    assert(darray_prepend(NULL, 0) == RET_INVALID_PARAMS);
    assert(darray_append(NULL, 0) == RET_INVALID_PARAMS);
    assert(darray_delete(NULL, 0) == RET_INVALID_PARAMS);
    assert(darray_insert(NULL, 0, 0) == RET_INVALID_PARAMS);
    assert(darray_set_by_index(NULL, 0, 0) == RET_INVALID_PARAMS);
    assert(darray_get_by_index(NULL, 0, NULL) == RET_INVALID_PARAMS);
    assert(darray_find(NULL, NULL, NULL) < 0);
    assert(darray_foreach(NULL, NULL, NULL) == RET_INVALID_PARAMS);
    printf("===========Warning is normal end==============\n");

    return;
}

static void single_thread_test(void)
{
    test_int_darray();
    test_invalid_params();

    return;
}

int main(int argc, char *argv[])
{
    single_thread_test();

    return 0;
}
#endif
