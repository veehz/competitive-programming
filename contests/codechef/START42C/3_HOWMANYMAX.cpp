#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;
typedef long double ld;

void solve(){
	int n; cin >> n; --n;
	string s; cin >> s;
	int ans = 0;
	ans += (s[0]=='1');
	ans += (s.back()=='0');
	for(int i=0;i<n-1;i++) ans += (s[i]=='0' && s[i+1]=='1');
	cout << ans << endl;
}

int main() {
  int t;
  cin >> t;
  while (t--) solve();
}
