#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;

map<int,int> mp;
int get_factors(int a)
{
	if(mp.find(a) != mp.end())
		return mp[a];
	int cnt = 2;
	int i;
	for(i = 2; i < sqrt(a); i++)
		if(a % i == 0)
			cnt += 2;
	if(i * i == a)
		cnt++;
	return mp[a] = cnt;
}

int main()
{
	int n;
	scanf("%d",&n);
	vector<int> an(n);
	vector<int> bn(n);
	int tmp;
	mp[1] = 1;
	for (int i = 0; i < n; i++){
		scanf("%d", &tmp);
		an[i] = get_factors(tmp);
	}
	for (int i = 0; i < n; i++){
		scanf("%d", &tmp);
		bn[i] = get_factors(tmp);

	}
	sort(an.begin(), an.end());
	sort(bn.begin(), bn.end());
	int cnt = 0;
	int idx = 0;
	for(int i = 0; i < n; i++){
		while(idx < n){
			if(an[idx] > bn[i]){
				cnt++;
				idx++;
				break;
			}
			idx++;
		}
	}
	printf("%d\n", cnt);
	return 0;
}