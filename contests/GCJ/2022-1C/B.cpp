/* MGod. */
#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

void solve() {
	int n,k; cin >> n >> k;
	vector<ll> a(n); for(auto& x : a) cin >> x;

	ll s = accumulate(a.begin(), a.end(), 0LL);
	ll ss = 0; for(auto& x : a) ss += x*x;
	
	// cout << s*s << ' ' << ss << endl;
	ll x = s*s - ss;

	if(s == 0){
		if(ss == 0){
			cout << 0 << endl;
		} else cout << "IMPOSSIBLE" << endl;
		return;
	}

	if(x % (2*s) == 0) {
		cout << -x/(2*s) << endl;
		return;
	}

	if(k == 1){
		cout << "IMPOSSIBLE" << endl;
		return;
	}

	assert(x%2==0);
	ll b = x/2;
	ll y = -s*s + b - s;
	ll xx = -(s*y+b)/(s+y);

	// test
	// {
	// 	ll aa = s+xx+y;
	// 	aa *= aa;
	// 	ll bb = ss + xx*xx + y*y;
	// 	assert(aa==bb);
	// }

	cout << xx << ' ' << y << endl;
	return;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	int t; cin >> t;
	for(int i=0;i<t;i++){
		cout << "Case #" << i+1 << ": ";
		solve();
	}
}

