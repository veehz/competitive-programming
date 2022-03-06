#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;

void solve() {
	return;
}

vector<vector<int>> operations;
int main() {
	int n; cin >> n;
	bool has[n][n];
	vector<int> rep[n];
	int l = 0;
	for(int i=0;i<n;i++) for(int j=0;j<n;j++) has[i][j] = false;
	for(int i=0;i<n;i++) for(int j=0;j<n;j++){
		int k; cin >> k;
		if(!has[i][k-1]){
			has[i][k-1] = true;
		} else { ++l; rep[i].push_back(k); }
	}
	// for(int i=0;i<n;i++) cout << rep[i] << endl;
	vector<int> now;
	while(l){
		now.assign(n,-1);
		for(int i=0;i<n;i++){
			if(rep[i].size()) { now[i] = rep[i].back(); rep[i].pop_back(); --l; }
			else if(now[(i+n-1)%n]){ now[i] = now[(i+n-1)%n]; has[i][now[i]-1] = false; }
		}
		for(int i=0;i<n;i++) if(now[i] == -1) { now[i] = now[(i+n-1)%n]; has[i][now[i]-1] = false; }
		for(int i=0;i<n;i++){
			int given = now[(i+n-1)%n];
			if(!has[i][given-1]) has[i][given-1] = true;
			else { ++l; rep[i].push_back(given); }
		}
		operations.push_back(now);
	}
	for(int d=1;d<n;d++){
		vector<int> spin(n);
		for(int i=1;i<=n;i++) spin[i-1] = (i+d-1)%n+1;
		for(int i=0;i<d;i++){
			operations.push_back(spin);
			rotate(spin.begin(),spin.begin()+n-1,spin.end());
		}
	}
	cout << operations.size() << endl;
	for(auto s : operations){
		for(auto k : s) cout << k << ' ';
		cout << endl;
	}
}
