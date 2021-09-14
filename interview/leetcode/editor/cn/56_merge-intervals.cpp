#include <bits/stdc++.h>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        const int n = intervals.size();
        if(n == 0)
            return vector<vector<int>>();
        else if ( n == 1)
            return intervals;
        vector<vector<int>> ret;
        sort(intervals.begin(), intervals.end(), [](const vector<int> &a, const vector<int> &b) -> bool {
            return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
        });
        int a = intervals[0][0], b = intervals[0][1];
        for(int i = 1; i < n; i++){
            if(intervals[i][0] > b){
                ret.push_back({a,b});
                a = intervals[i][0];
                b = intervals[i][1];
            }
            else{
                b = max(b,intervals[i][1]);
            }
        }
        ret.push_back({a,b});
        return ret;
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main()
{
    Solution s;
    return 0;
}

//Given an array of intervals where intervals[i] = [starti, endi], merge all ove
//rlapping intervals, and return an array of the non-overlapping intervals that co
//ver all the intervals in the input. 
//
// 
// Example 1: 
//
// 
//Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
//Output: [[1,6],[8,10],[15,18]]
//Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
// 
//
// Example 2: 
//
// 
//Input: intervals = [[1,4],[4,5]]
//Output: [[1,5]]
//Explanation: Intervals [1,4] and [4,5] are considered overlapping.
// 
//
// 
// Constraints: 
//
// 
// 1 <= intervals.length <= 104 
// intervals[i].length == 2 
// 0 <= starti <= endi <= 104 
// 
// Related Topics 排序 数组 
// 👍 730 👎 0
