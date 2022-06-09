#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;
typedef long double ld;

void solve(){
	int n; cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++) cin >> a[i];
	int cur_min = a[0];
	int cur_max = a[0];
	for(int i=1;i<n;i++){
		if(a[i] > cur_min && a[i] < cur_max) {
			cout << "NO" << endl;
			return;
		}
		cur_min = min(cur_min, a[i]);
		cur_max = max(cur_max, a[i]);
	}
	cout << "YES" << endl;
}

int main() {
  int t;
  cin >> t;
  while (t--) solve();
}
