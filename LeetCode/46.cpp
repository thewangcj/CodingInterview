// 给定一个 没有重复 数字的序列，返回其所有可能的全排列。

// 示例:

// 输入: [1,2,3]
// 输出:
// [
//   [1,2,3],
//   [1,3,2],
//   [2,1,3],
//   [2,3,1],
//   [3,1,2],
//   [3,2,1]
// ]
#include <iostream>
#include <vector>
using namespace std;
//全排列递归实现
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