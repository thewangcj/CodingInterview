#include "../../data_structure/tools.h"
#include <stdint.h>

int qsearch(void **array, size_t nr, void *data, DataCompareFunc cmp)
{
    int low    = 0;
    int mid    = 0;
    int high   = nr - 1;
    int result = 0;

    return_val_if_fail(array != NULL && cmp != NULL, -1);

    while (low <= high) {
        mid    = low + ((high - low) >> 1);
        result = cmp(array[mid], data);

        if (result == 0) {
            return mid;
        } else if (result < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

#define SEARCH_TEST
#ifdef SEARCH_TEST
#include <assert.h>
int int_cmp(void *a, void *b) { return (uint64_t)a - (uint64_t)b; }

static void search_test(size_t n)
{
    int i           = 0;
    uint64_t *array = (uint64_t *)malloc(n * sizeof(uint64_t));

    for (i = 0; i < n; i++) {
        array[i] = i;
    }

    for (i = 0; i < n; i++) {
        assert(qsearch((void **)array, n, (void *)i, int_cmp) == i);
    }

    free(array);

    return;
}

int main(int argc, char *argv[])
{
    int i = 0;
    for (i = 1; i < 1000; i++) {
        search_test(i);
    }

    return 0;
}
#endif /*QSEARCH_TEST*/
