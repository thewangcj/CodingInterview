/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */
#include <vector>
#include <iostream>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int>::iterator iter;
        vector<int>::iterator res;

        for (iter = nums.begin(); iter != nums.end(); iter++)
        {
            cout << *iter << " ";
            res = find(iter + 1, nums.end(), target - *iter);

            if (res != nums.end())
            {
                cout << "found" << endl;
                return vector<int>{(int)(iter - nums.begin()), (int)(res - nums.begin())};
            };
        }
        return vector<int>();
    }
};
// @lc code=end

