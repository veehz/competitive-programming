#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;

vector<ll> fact;
vector<pair<ll,int>> all;

void init(){
	int n = fact.size();
	for(int mask=0;mask<(1<<n);mask++){
		ll k = 0;
		int cnt = 0;
		for(int i=0;i<n;i++) if(mask&(1<<i)) { k += fact[i]; cnt++; }
		all.pb({k,cnt});
	}
	sort(all.begin(),all.end());
}

void solve() {
	ll n; cin >> n;
	int ans = __builtin_popcountll(n);
	for(auto [k,cnt] : all){
		if(k > n) break;
		ans = min(ans, __builtin_popcountll(n-k) + cnt);
	}
	cout << ans << endl;
	return;
}

int main() {
	fact.pb(1);
	for(ll i=1;;i++){
		if(fact.back() * i >= 1e12) break;
		fact.pb(fact.back() * i);
	}
	init();
	
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	int t; cin >> t;
	for(int i=0;i<t;i++) solve();
}
