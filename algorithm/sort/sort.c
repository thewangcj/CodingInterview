#include "sort.h"
#include <bits/stdint-uintn.h>
static void sort_array_print(void **array, int n)
{
    int i      = 0;
    int *dummy = (int *)array;
    for (i = 0; i < n; i++) {
        printf("%d ", dummy[i]);
    }
    printf("\n");
}

// 气泡排序
Ret bubble_sort(void **array, size_t nr, DataCompareFunc cmp)
{
    size_t i     = 0;
    size_t max   = 0;
    size_t right = 0;
    return_val_if_fail(array != NULL && cmp != NULL, RET_INVALID_PARAMS);

    if (nr < 2) {
        return RET_OK;
    }

    for (right = nr - 1; right > 0; right--) {
        for (i = 1, max = 0; i < right; i++) {
            if (cmp(array[i], array[max]) > 0) {
                max = i;
            }
        }

        if (cmp(array[max], array[right]) > 0) {
            void *data   = array[right];
            array[right] = array[max];
            array[max]   = data;
        }
    }

    return RET_OK;
}

// 快排
void quick_sort_impl(void **array, size_t left, size_t right,
                     DataCompareFunc cmp)
{
    size_t save_left  = left;
    size_t save_right = right;
    void *x           = array[left];

    while (left < right) {
        while (cmp(array[right], x) >= 0 && left < right)
            right--;
        if (left != right) {
            // 这里的写法有点特殊
            array[left] = array[right];
            left++;
        }

        while (cmp(array[left], x) <= 0 && left < right)
            left++;
        if (left != right) {
            array[right] = array[left];
            right--;
        }
    }
    array[left] = x;

    if (save_left < left) {
        quick_sort_impl(array, save_left, left - 1, cmp);
    }

    if (save_right > left) {
        quick_sort_impl(array, left + 1, save_right, cmp);
    }

    return;
}

Ret quick_sort(void **array, size_t nr, DataCompareFunc cmp)
{
    Ret ret = RET_OK;

    return_val_if_fail(array != NULL && cmp != NULL, RET_INVALID_PARAMS);

    if (nr > 1) {
        quick_sort_impl(array, 0, nr - 1, cmp);
    }

    return ret;
}

// 通常的归并排序会频繁的 malloc free，这里用了一个数组来存放排序后的结果
// 看似归并排序与快速排序相比 几乎没有优势可言，
// 但是归并排序更重要的能力在于处理大量数据的排序，它不要求被排序的数据全部在内存中，
// 所以在数据大于内存的容纳能力时，归并排序就更能大展身手了。
// 归并排序最常用的地方是数据库管理系统(DBMS)，因为数据库中存储的数据通常无法全部加载到内存中来的
static Ret merge_sort_impl(void **storage, void **array, size_t low, size_t mid,
                           size_t high, DataCompareFunc cmp)
{
    size_t i = low;
    size_t j = low;
    size_t k = mid;

    if ((low + 1) < mid) {
        size_t x = low + ((mid - low) >> 1);
        merge_sort_impl(storage, array, low, x, mid, cmp);
    }

    if ((mid + 1) < high) {
        size_t x = mid + ((high - mid) >> 1);
        merge_sort_impl(storage, array, mid, x, high, cmp);
    }

    while (j < mid && k < high) {
        if (cmp(array[j], array[k]) <= 0) {
            storage[i++] = array[j++];
        } else {
            storage[i++] = array[k++];
        }
    }

    while (j < mid) {
        storage[i++] = array[j++];
    }

    while (k < high) {
        storage[i++] = array[k++];
    }

    for (i = low; i < high; i++) {
        array[i] = storage[i];
    }

    return RET_OK;
}

Ret merge_sort(void **array, size_t nr, DataCompareFunc cmp)
{
    void **storage = NULL;
    Ret ret        = RET_OK;

    return_val_if_fail(array != NULL && cmp != NULL, RET_INVALID_PARAMS);

    if (nr > 1) {
        storage = (void **)malloc(sizeof(void *) * nr);
        if (storage != NULL) {
            ret = merge_sort_impl(storage, array, 0, nr >> 1, nr, cmp);

            free(storage);
        }
    }

    return ret;
}

#define SORT_TEST
#ifdef SORT_TEST
#include <assert.h>

int int_cmp(void *a, void *b) { return (uint64_t)a - (uint64_t)b; }

int int_cmp_invert(void *a, void *b) { return (uint64_t)b - (uint64_t)a; }

static void **create_int_array(int n)
{
    int i           = 0;
    uint64_t *array = (uint64_t *)malloc(sizeof(uint64_t) * n);

    for (i = 0; i < n; i++) {
        array[i] = (rand() % 100);
    }

    return (void **)array;
}

static void sort_test_one_asc(SortFunc sort, int n)
{
    int i        = 0;
    void **array = create_int_array(n);

    sort(array, n, int_cmp);

    for (i = 1; i < n; i++) {
        assert(array[i] >= array[i - 1]);
    }

    free(array);

    return;
}

static void sort_test_one_dec(SortFunc sort, int n)
{
    int i        = 0;
    void **array = create_int_array(n);
    // printf("before sort:");
    // sort_array_print(array, n);

    sort((void **)array, n, int_cmp_invert);
    // printf("after sort:");
    // sort_array_print(array, n);

    for (i = 1; i < n; i++) {
        assert(array[i] <= array[i - 1]);
    }
    free(array);

    return;
}

static void sort_test(const char *func_name, SortFunc sort)
{
    printf("%s\n", func_name);
    int i = 0;
    for (i = 0; i < 1000; i++) {
        sort_test_one_dec(sort, 10);
        sort_test_one_asc(sort, 10);
    }

    return;
}

int main(int argc, char *argv[])
{
    srand(100);
    printf("sizeof int:%zd, sizeof void *:%zd\n", sizeof(int), sizeof(void *));
    sort_test("bubble_sort", bubble_sort);
    sort_test("quick_sort", quick_sort);
    sort_test("merge_sort", merge_sort);

    return 0;
}
#endif /*SORT_TEST*/
