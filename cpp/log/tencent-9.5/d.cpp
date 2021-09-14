#include <iostream>
#include <map>
#include <vector>
using namespace std;

map<int, int> mp;

int get_len(int x)
{
    if (mp.find(x) != mp.end())
        return mp[x];
    if (x == 1 || x == 0)
        return mp[x] = 1;
    return mp[x] = 1 + get_len(x / 2) * 2;
}

int get_one(int l, int r, int k)
{
	if(l > r)
		return 0;
    int len = get_len(k);
    int mid = len / 2;
	if(l == 0 && r == len-1)
		return k;
    if (l > mid)
        return get_one(l - mid - 1, r - mid - 1, k / 2);
    else if (r < mid)
        return get_one(l, r, k/2);
    else
        return (k % 2 == 1 ? 1 : 0) + get_one(l, mid - 1, k / 2) + get_one(0, r - mid - 1, k / 2);
}

int main()
{
    int n, l, r;
    cin >> n >> l >> r;
    cout << get_one(l - 1, r - 1, n) << endl;
    return 0;
}