#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int n;
	cin >> n;
	string str;
	cin >> str;
	vector<int> v;
	long long ans = 0;
	int c_n = 0;
	for(int i=0; i<n; i++)
		if(str[i] == 'c'){
			ans += i - c_n; 
			c_n++;
		}
	cout << ans << endl;
	return 0;
}