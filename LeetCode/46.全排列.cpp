/*
 * @lc app=leetcode.cn id=46 lang=cpp
 *
 * [46] 全排列
 */
#include <vector>
#include <iostream>
using namespace std;
// @lc code=start
class Solution {
public:
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
            if (used[i] == false)
            {
                used[i] = true;
                a[depth] = i;
                dfs(depth + 1, n);
                used[i] = false;
            }
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
    }
};
// @lc code=end

