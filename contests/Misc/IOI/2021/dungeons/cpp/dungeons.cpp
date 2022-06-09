#ifdef LOCAL
#include "all.h"
#else
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#endif
using namespace std;
using namespace __gnu_pbds;
#include "dungeons.h"

typedef long long ll;

// SUBTASK 3
int n, lx;
vector<int> s,p,w,l;
vector<ll> win, cycle;
vector<bool> visited;
vector<vector<ll>> up;
vector<vector<ll>> cost;

ll findup(int x,int pow){
	if(x==n || x==-1) return -1;
	if(up[x][pow] >= 0) return up[x][pow];
	up[x][pow] = findup(up[x][pow-1], pow-1);
	if(up[x][pow] == -1) return -1;
	cost[x][pow] = cost[x][pow-1] + cost[up[x][pow-1]][pow-1];
	// cout << x << ' ' << pow << ' ' << up[x][pow] << ' ' << cost[x][pow] << endl;
	return up[x][pow];
}

void init(int N, vector<int> S, vector<int> P, vector<int> W, vector<int> L) {
	n=N; s=S; p=P; w=W; l=L;
	lx = ceil(log2(n));
	up.assign(n+1, vector<ll>(lx+1,-1));
	cost.assign(n+1, vector<ll>(lx+1,(ll)1e18));
	win.assign(n+1,0);
	for(int i=n;i--;){
		win[i] = (ll)s[i] + win[w[i]];
	}
	//for(int i : win) cout << "w " << i << endl;
	unordered_map<int,bool> thispath;
	visited.assign(n,false);
	cycle.assign(n,-1);
	for(int i=0;i<n;i++){
		if(visited[i]) continue;
		thispath.clear();
		int now = i;
		while(true){
			if(now == n) break;
			if(visited[now] && !thispath[now]) break;
			if(thispath[now]){
				vector<int> cyc;
				ll total = 0;
				int head = now;
				do {
					cyc.push_back(head);
					total += p[head];
					head = l[head];
				} while(head != now);
				for(int k : cyc) cycle[k] = total;
				
				for(int x=0;x<(int)cyc.size();x++){ up[cyc[x]][0] = l[cyc[x]]; cost[cyc[x]][0] = p[cyc[x]]; }
				for(int i=1;i<=lx;i++){
					for(int x=0;x<(int)cyc.size();x++){
						up[cyc[x]][i] = cyc[(x + (1<<i))%cyc.size()];
						cost[cyc[x]][i] = cost[up[cyc[x]][i-1]][i-1] + cost[cyc[x]][i-1];
						//cout << cyc[x] << ' ' << i << ' ' << up[cyc[x]][i] << ' ' << cost[cyc[x]][i] << endl;
					}
				}
				
				break;
			}
			visited[now] = thispath[now] = true;
			now = l[now];
		}
	}
	for(int i=0;i<n;i++){
		up[i][0] = l[i];
		cost[i][0] = p[i];
	}
	for(int i=1;i<=lx;i++){
		for(int x=0;x<n;x++){
			findup(x,i);
		}
	}
	return;
}

long long simulate(int x, int Z) {
	ll z = Z;
	while(x != n){
		if(z < s[x]){
			ll rds = (s[x] - z);
			if(cycle[x] > 0 && rds/cycle[x] != 0){
				z += rds/cycle[x] * cycle[x];
			} else {
				ll need = (s[x] - z);
				ll rounds = lx;
				while(rounds > 0 && cost[x][rounds] > need) rounds--;
				//cout << "walk from " << x << " to " << up[x][rounds] << " for cost " << cost[x][rounds];
				z += cost[x][rounds];
				x = up[x][rounds];
				//cout << "ended with " << x << ' ' << z << endl;
			}
		} else {
			z += win[x];
			break;
		}
		//cout << 'z' << x << ' ' << z << endl;
	}
	return z;
}

#ifdef LOCAL
long long brute_simulate(int x, int Z) {
	ll z = Z;
	while(x != n){
		if(z >= s[x]){
			z += s[x];
			x = w[x];
		} else {
			z += p[x];
			x = l[x];
		}
	}
	return z;
}

int cnt = 0;
void call(int P, int q){
	ll A = simulate(P,q);
	ll B = brute_simulate(P,q);
	if(A==B) cout << "AC " << cnt << endl;
	else{
		cout << A << ' ' << B << endl;
		cout << n << endl;
		for(int i : p) cout << i << ' ';
		cout << endl;
		for(int i : w) cout << i << ' ';
		cout << endl;
		for(int i : l) cout << i << ' ';
		cout << endl;
		assert(false);
	}
	cnt++;
}
int main(){
	int lm = 88847394;
	init(3,{lm,lm,lm},{3,1,2},{2,2,3},{1,0,1});
	call(0,1); call(2,3);
	for(int i=0;i<3;i++){
		for(int j=0;j<6;j++){
			call(i,j);
		}
	}
	while(true){
		int m = rand()%10+1;
		lm = rand()%10000+1;
		vector<int> S(m,lm),P(m),W(m),L(m);
		for(int i=0;i<m;i++){
			P[i] = rand()%(lm+1000) + 1;
			W[i] = rand()%(m-i) + i + 1;
			L[i] = rand()%m + 1;
		}
		init(m,S,P,W,L);
		for(int i=0;i<m;i++){
			for(int k=0;k<50;k++){
				call(i, rand()%m+1);
			}
		}
	}
}
#endif
