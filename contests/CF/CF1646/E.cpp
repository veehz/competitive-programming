#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;

vector<bool> vis;
ll cnt = 1;

// 21 * 10^6
vector<ll> u(21);
vector<bool> vv(21*1000000+1);

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	int n,m; cin >> n >> m;
	vis.assign(n+1,false);
	
	{
		ll cur = 0;
		for(int i=0;i<21;i++){
			for(int j=0;j<m;j++){
				if(!vv[(i+1)*(j+1)]){
					cur++;
					vv[(i+1)*(j+1)] = true;
				}
			}
			u[i] = cur;
		}
	}
	
	for(ll i=2;i<=n;i++){
		if(vis[i]) continue;
		int p=1;
		while(pow(i,p) <= n){
			vis[pow(i,p)] = true;
			p++;
		}
		p--;
		cnt += u[p-1];
	}
	
	cout << cnt << endl;
}

