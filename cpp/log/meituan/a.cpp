#include <iostream>
#include <vector>
using namespace std;
const long long mod = 998244353;

int main()
{
    int n;
    cin >> n;
    vector<vector<long long>> v(n, vector<long long>(2, 0));
    v[0][0] = v[0][1] = 1;
    v[1][0] = v[1][1] = 2;
    for (int i = 2; i < n; i++) {
		v[i][0] = (v[i-1][0] + v[i-2][1]) % mod;
		v[i][1] = (v[i-1][1] + v[i-2][0]) % mod;
    }
	cout << (v[n-1][0] + v[n-1][1])%mod << endl;
    return 0;
}