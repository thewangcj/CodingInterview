/*
 * @lc app=leetcode.cn id=46 lang=cpp
 *
 * [46] 全排列
 */
#include <cstddef>
#include <iostream>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
  public:
    /**
        void dfs(int depth, int n)
        {
            if (depth >= n)
            {
                for (int i = 0; i < 3; i += 1)
                {
                    cout << a[i] << " ";
                }
                cout << endl;
                return;
            }
            for (int i = 1; i <= n; i += 1)
            {
                // 尝试没有标记过的数
                if (used[i] == false)
                {
                    // 标记
                    used[i] = true;
                    a[depth] = i;
                    dfs(depth + 1, n);
                    // 撤回标记
                    used[i] = false;
                }
            }
        }
     */
    void dfs(vector<vector<int>> &res, vector<int> &output, int depth, int n)
    {
        if (depth >= n) {
            res.emplace_back(output);
            return;
        }
        for (int i = depth; i <= n; i += 1) {
            swap(output[i], output[depth]);
        }
    }
    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<vector<int>> res;
        size_t len = nums.size();
        return res;
    }
};
// @lc code=end
