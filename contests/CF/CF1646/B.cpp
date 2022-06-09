#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;

void solve() {
	int n; cin >> n;
	vector<ll> a(n); for(int i=0;i<n;i++) cin >> a[i];
	sort(a.begin(),a.end());
	vector<ll> pre(n); pre[0] = a[0]; for(int i=1;i<n;i++) pre[i] = pre[i-1] + a[i];
	for(int cr=1;cr<n;cr++){
		if(pre[cr-1+1] < pre[n-1] - pre[n-cr-1]){
			cout << "YES" << endl;
			return;
		}
	}
	cout << "NO" << endl;
	return;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	int t; cin >> t;
	for(int i=0;i<t;i++) solve();
}
