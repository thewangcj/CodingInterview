/*
1. 两数之和

给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。


示例:

给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]

*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
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

int main()
{
    Solution s = Solution();
    vector<int> test1{3, 2, 4};
    vector<int> res = s.twoSum(test1, 6);
    vector<int>::iterator iter;
    cout << endl;
    for (iter = res.begin(); iter != res.end(); iter++)
        cout << *iter << " ";

    // vector<int>test2{10,11,13,14,5,6};
    // res = s.twoSum(test2, 11);
    // for(iter = res.begin(); iter != res.end(); iter++)
    //     cout << *iter << " ";
}