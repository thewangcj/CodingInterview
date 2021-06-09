class Solution {
public:
    int across_number(vector<int>&arr, int l, int mid, int r)
    {
        int n = r - l + 1;
        int *temp = (int *)malloc(sizeof(int) * n);
        int p1 = l, p2 = mid + 1, k = 0, num = 0;
        while (p1 <= mid || p2 <= r)
        {
            if (p2 > r || (p1 <= mid && arr[p1] <= arr[p2]))
            {
                temp[k++] = arr[p1++];
            }
            else
            {
                num += mid - p1 + 1;
                temp[k++] = arr[p2++];
            }
        }
        for (int i = 0, j = l; i < n; i++, j++)
        {
            arr[j] = temp[i];
        }
        free(temp);
        return num;
    }

    int inversion_number(vector<int>&arr, int l, int r) {
        if (l == r) return 0;
        int mid = (l + r) >> 1;
        int a = inversion_number(arr, l, mid);
        int b = inversion_number(arr, mid + 1, r);
        int c = across_number(arr, l, mid, r);
        return a + b + c;
    }
    int reversePairs(vector<int>& nums) {
        if(nums.empty()) return 0;
        return inversion_number(nums, 0, nums.size() - 1);
    }
};