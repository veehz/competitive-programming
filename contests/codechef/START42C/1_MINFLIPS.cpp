#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;
typedef long double ld;

void solve(){
	int n; cin >> n;
	vector<int> a(2);
	for(int x,i=0;i<n;i++){
		cin >> x;
		if(x < 0) a[0]++;
		else a[1]++;
	}
	if(n&1) {
		cout << -1 << endl;
		return;
	} else {
		cout << abs(n/2 - a[0]) << endl;
		return;
	}
}

int main() {
  int t;
  cin >> t;
  while (t--) solve();
}

