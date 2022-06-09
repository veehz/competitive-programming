#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;

void solve() {
	unsigned long long n,s; cin >> n >> s;
	cout << s/(n*n) << endl;
	return;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	int t; cin >> t;
	for(int i=0;i<t;i++) solve();
}
