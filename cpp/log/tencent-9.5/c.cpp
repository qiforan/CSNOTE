#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int n;
	cin >> n;
	string str;
	cin >> str;
	if(n == 1) return 1;
	vector<vector<int>> dp(n, vector<int>(2));
	dp[0][0] = dp[0][1] = 1;
	for(int i = 1; i < n; i++) {
		dp[i][0] = dp[i][1] = 1;
		for(int j = 0; j < i; j++){
			if(str[i] == str[j]){
				if(dp[j][0] + dp[j][1] + 1 >= dp[i][0]){
					dp[i][0] = dp[j][0] + dp[j][1] + 1;
					if(dp[j][1] + dp[j][0] + 1 == dp[i][0]){
						dp[i][1] = max(dp[i][1], dp[j][1] + 1);
					}
				}
			}
			else{
				if(dp[j][0] + 1 >= dp[i][0]){
					dp[i][0] = dp[j][0] + 1;
					dp[i][1] = 1;
				}
			}
		}
	}
	cout << dp[n-1][0] << endl;
	return 0;
}