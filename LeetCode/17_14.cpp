// 设计一个算法，找出数组中最小的k个数。以任意顺序返回这k个数均可。

// 示例：

// 输入： arr = [1,3,5,7,2,4,6,8], k = 4
// 输出： [1,2,3,4]
// 提示：

// 0 <= len(arr) <= 100000
// 0 <= k <= min(100000, len(arr))
class Solution
{
public:
    vector<int> smallestK(vector<int> &arr, int k)
    {
        priority_queue<int> pq;
        vector<int> result;
        for (auto ele : arr)
        {
            pq.push(ele);
            if (pq.size() > k)
                pq.pop();
        }
        while (!pq.empty())
        {
            result.push_back(pq.top());
            pq.pop();
        }
        return result;
    }
};