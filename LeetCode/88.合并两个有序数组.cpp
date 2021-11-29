/*
 * @lc app=leetcode.cn id=88 lang=cpp
 *
 * [88] 合并两个有序数组
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
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
};
// @lc code=end

