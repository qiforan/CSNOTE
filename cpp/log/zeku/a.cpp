#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 计算两个矩阵的乘积
     * @param A int整型vector<vector<>> 输入左矩阵
     * @param B int整型vector<vector<>> 输入右矩阵
     * @return int整型vector<vector<>>
     */
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B)
    {
        // write code here
		int m = A.size();
		int n = A[0].size();
		int k = B[0].size();
		vector<vector<int>> v(m, vector<int>(k));
		for(int i = 0; i < m; i++)
			for(int j = 0; j < k; j++){
				int e = 0;
				for(int l = 0; l < n; l++)
					e += A[i][l] *  B[l][j];
				v[i][j] = e;
			}
		return v;
    }
};

int main()
{
	Solution s;
	vector<vector<int>> A {{1,2}};
	vector<vector<int>> B {{3},{4}};
	s.multiply(A, B);
	return 0;
}