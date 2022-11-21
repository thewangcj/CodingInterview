#include "d_list.h"
#include <assert.h>
#include <stdio.h>

static int cmp_int(void *ctx, void *data) { return (int)data - (int)ctx; }

static D_LIST_RET print_int(void *ctx, void *data)
{
    printf("%d ", (int)data);

    return DLIST_RET_OK;
}

static D_LIST_RET check_and_dec_int(void *ctx, void *data)
{
    int *expected = (int *)ctx;
    assert(*expected == (int)data);

    (*expected)--;

    return DLIST_RET_OK;
}

void test_int_dlist(void)
{
    size_t i      = 0;
    size_t n      = 100;
    size_t data   = 0;
    d_list *dlist = dlist_create(NULL, NULL);
    printf("dlist_len: %zd\n", dlist_length(dlist));

    for (i = 0; i < n; i++) {
        assert(dlist_append(dlist, (void *)i) == DLIST_RET_OK);
        assert(dlist_length(dlist) == (i + 1));
        assert(dlist_get_by_index(dlist, i, (void **)&data) == DLIST_RET_OK);
        assert(data == i);
        assert(dlist_set_by_index(dlist, i, (void *)(2 * i)) == DLIST_RET_OK);
        assert(dlist_get_by_index(dlist, i, (void **)&data) == DLIST_RET_OK);
        assert(data == 2 * i);
        assert(dlist_set_by_index(dlist, i, (void *)i) == DLIST_RET_OK);
        assert(dlist_find(dlist, cmp_int, (void *)i) == i);
    }

    for (i = 0; i < n; i++) {
        assert(dlist_get_by_index(dlist, 0, (void **)&data) == DLIST_RET_OK);
        assert(data == (i));
        assert(dlist_length(dlist) == (n - i));
        assert(dlist_delete(dlist, 0) == DLIST_RET_OK);
        assert(dlist_length(dlist) == (n - i - 1));
        if ((i + 1) < n) {
            assert(dlist_get_by_index(dlist, 0, (void **)&data) ==
                   DLIST_RET_OK);
            assert((int)data == (i + 1));
        }
    }

    assert(dlist_length(dlist) == 0);

    for (i = 0; i < n; i++) {
        assert(dlist_prepend(dlist, (void *)i) == DLIST_RET_OK);
        assert(dlist_length(dlist) == (i + 1));
        assert(dlist_get_by_index(dlist, 0, (void **)&data) == DLIST_RET_OK);
        assert(data == i);
        assert(dlist_set_by_index(dlist, 0, (void *)(2 * i)) == DLIST_RET_OK);
        assert(dlist_get_by_index(dlist, 0, (void **)&data) == DLIST_RET_OK);
        assert(data == 2 * i);
        assert(dlist_set_by_index(dlist, 0, (void *)i) == DLIST_RET_OK);
    }

    i = n - 1;
    assert(dlist_foreach(dlist, check_and_dec_int, &i) == DLIST_RET_OK);

    size_t s = dlist_length(dlist);
    for (i = 1; i < n; i++) {
        assert(dlist_insert(dlist, i, (void *)i) == DLIST_RET_OK);
        printf("dlist len: %zd, s:%zd, i: %zd, s + i: %zd\n",
               dlist_length(dlist), s, i, s + i);
        assert(dlist_length(dlist) == (s + i));
        assert(dlist_get_by_index(dlist, i, (void **)&data) == DLIST_RET_OK);
        assert(data == i);
        assert(dlist_set_by_index(dlist, i, (void *)(2 * i)) == DLIST_RET_OK);
        assert(dlist_get_by_index(dlist, i, (void **)&data) == DLIST_RET_OK);
        assert(data == 2 * i);
        assert(dlist_set_by_index(dlist, i, (void *)i) == DLIST_RET_OK);
    }

    dlist_destroy(dlist);

    return;
}

void test_invalid_params(void)
{
    printf("===========Warning is normal begin==============\n");
    assert(dlist_length(NULL) == 0);
    assert(dlist_prepend(NULL, 0) == DLIST_RET_INVALID_PARAMS);
    assert(dlist_append(NULL, 0) == DLIST_RET_INVALID_PARAMS);
    assert(dlist_delete(NULL, 0) == DLIST_RET_INVALID_PARAMS);
    assert(dlist_insert(NULL, 0, 0) == DLIST_RET_INVALID_PARAMS);
    assert(dlist_set_by_index(NULL, 0, 0) == DLIST_RET_INVALID_PARAMS);
    assert(dlist_get_by_index(NULL, 0, NULL) == DLIST_RET_INVALID_PARAMS);
    assert(dlist_find(NULL, NULL, NULL) == DLIST_RET_INVALID_PARAMS);
    assert(dlist_foreach(NULL, NULL, NULL) == DLIST_RET_INVALID_PARAMS);
    printf("===========Warning is normal end==============\n");

    return;
}

static D_LIST_RET str_toupper(void *ctx, void *data)
{
    char *p = (char *)data;
    if (p != NULL) {
        while (*p != '\0') {
            if (islower(*p)) {
                *p = toupper(*p);
            }
            p++;
        }
    }

    return DLIST_RET_OK;
}

static void test_dlist_str_const()
{
    d_list *dlist = dlist_create(NULL, NULL);
    dlist_append(dlist, "It");
    dlist_append(dlist, "is");
    dlist_append(dlist, "OK");
    dlist_append(dlist, "!");
    dlist_foreach(dlist, str_toupper, NULL);
    dlist_destroy(dlist);
}

int main(int argc, char *argv[])
{
    test_int_dlist();

    test_invalid_params();

    test_dlist_str_const();

    return 0;
}
