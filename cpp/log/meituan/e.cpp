#include <iostream>
#include <vector>
#include <stack>
using namespace std;
int main()
{
	int n,m;
	cin >> n >> m;
	vector<int> v(n);
	for (int i = 0; i < n; i++)
		cin >> v[i];
	vector<int> sum(n);
	vector<int> max_e(n);
	vector<int> min_e(n);
	stack<int> 
	sum[0] = v[0];
	int max_sum = sum[0 + m - 1];
	int ans = 0;
	for (int i = 1; i + m -1 < n; i++)
		if(sum[i+m-1] - sum[i-1] > max_sum){
			max_sum = sum[i+m-1];
			ans = i;
		}
	cout << ans + 1 << endl;
	return 0;
}