#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;
typedef long double ld;

void solve(){
	int n,k; cin >> n >> k;
	int ans = 0;
	for(int i=0;i<=29;i++){
		int x = min(k/(1<<i),n);
		if(x==0) continue;
		if((k-x*(1<<i))%(1<<(i+1)) != 0) --x;
		ans += x;
		k -= x*(1<<i);
	}
	cout << ans << endl;
}

int main() {
  int t;
  cin >> t;
  while (t--) solve();
}
