#include<iostream>
#include<vector>
using namespace std;
const int max_val = 10000;

int main()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int> > v(n+1, vector<int>(n+1,max_val)); 
	vector<vector<int>> bus(m+1);
	for (int i = 1; i <= n; i++){
		v[i][i] = 0;
		int k;
		cin >> k;
		for (int j = 0; j < k; j++){
			int a;
			cin >> a;
			bus[a].push_back(i);
		}
	}
	for (int i = 1; i <= m; i++){
		for (int j = 0; j < bus[i].size(); j++){
			for (int k = 0; k < bus[i].size(); k++){
				if(j != k){
					v[bus[i][j]][bus[i][k]] = 1;
				}
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			for(int k = 1; k <= n; k++){
				if(v[i][k] != max_val && v[k][j] != max_val && v[i][k] + v[k][j] < v[i][j])
					v[i][j] = v[j][i] = v[i][k] + v[k][j];
			}
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++) {
			if(v[i][j] == max_val)
				cout << "-1";
			else
				cout << v[i][j];
			if(j != n) cout << " ";
		}
		cout << endl;
	}
	return 0;
}