#include <stdio.h>
#include <stdlib.h>

void merge(int *arr, int l, int mid, int r)
{
    int n = r - l + 1;
    int *temp = (int *)malloc(sizeof(int) * n);
    int p1 = l, p2 = mid + 1, k = 0;
    // 当两个数组中某一个还有元素的时候，合并过程继续
    while (p1 <= mid || p2 <= r)
    {
        if (p2 > r || (p1 <= mid && arr[p1] <= arr[p2]))
        {
            temp[k++] = arr[p1++];
        }
        else
        {
            temp[k++] = arr[p2++];
        }
    }
    for (int i = 0, j = l; i < n; i++, j++)
    {
        arr[j] = temp[i];
    }
    free(temp);
    return;
}

void merge_sort(int *arr, int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    merge_sort(arr, l, mid);
    merge_sort(arr, mid + 1, r);
    merge(arr, l, mid, r);
    return;
}