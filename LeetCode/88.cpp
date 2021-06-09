
#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
{
    int p_r = m + n - 1;
    int p1 = m - 1;
    int p2 = n - 1;
    while (p1 >= 0 && p2 >= 0)
    {
        if (nums2[p2] >= nums1[p1])
        {
            nums1[p_r] = nums2[p2];
            p2--;
            p_r--;
        }
        else
        {
            nums1[p_r] = nums1[p1];
            p1--;
            p_r--;
        }
    }
    while (p1 >= 0)
    {
        nums1[p_r] = nums1[p1];
        p1--;
        p_r--;
    }
    while (p2 >= 0)
    {
        nums1[p_r] = nums2[p2];
        p2--;
        p_r--;
    }
}

// void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
// {
//     auto p_r = nums1.rbegin();

//     auto p1 = nums1.rbegin() + n;
//     auto p2 = nums2.rbegin();
//     while (p1 != nums1.rend() && p2 != nums2.rend())
//     {
//         if (*p1 >= *p2)
//         {
//             *p_r++ = *p1++;
//         }
//         if (*p1 < *p2)
//         {
//             *p_r++ = *p2++;
//         }
//     }
//     while (p1 != nums1.rend())
//     {
//         *p_r++ = *p1++;
//     }
//     while (p2 != nums2.rend())
//     {
//         *p_r++ = *p2++;
//     }
// }

int main()
{
    vector<int> nums1(4);
    nums1[0] = 10;
    for (auto ele : nums1)
        cout << ele << " ";
    cout << endl;
    vector<int> nums2{2, 5, 6};

    merge(nums1, 1, nums2, 3);
    for (auto ele : nums1)
        cout << ele << " ";
    cout << endl;
    return 0;
}