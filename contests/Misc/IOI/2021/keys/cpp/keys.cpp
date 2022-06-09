#ifdef LOCAL
#include "all.h"
#else
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;
#endif

#define pb push_back

vector<bool> visited;
vector<bool> keys;
vector<vector<int>> pending;
vector<vector<vector<int>>> edges;
vector<int> res;

vector<int> find_reachable(vector<int> r, vector<int> u, vector<int> v, vector<int> c) {
	int n = r.size(), m = u.size();
	res.assign(n,0);
	
	edges.assign(30,vector<int>(n));
	for(int i=0;i<m;i++){
		edges[c[i]][u[i]].pb(i);
		edges[c[i]][v[i]].pb(i);
	}
	
	int mincnt = (int)1e9;
	
	for(int i=0;i<30;i++){
		
	}
	
	queue<int> q;
	for(int i=0;i<n;i++){
		visited.assign(n,false);
		keys.assign(n,false);
		pending.assign(n,{});
		keys[r[i]] = true;
		//visited[i] = true;
		q.push(i);
		
		while(!q.empty()){
			int s = q.front(); q.pop();
			if(visited[s]) continue;
			visited[s] = true;
			
			keys[r[s]] = true;
			if(pending[r[s]].size()){
				for(int k : pending[r[s]]) if(!visited[k]) q.push(k);
				pending[r[s]].clear();
			}
			
			for(int j : edges[s]){
				int k = (u[j]==s?v[j]:u[j]);
				if(visited[k]) continue;
				//cout << s << ' ' << k << endl;
				if(!keys[c[j]]){
					pending[c[j]].pb(k);
				} else {
					q.push(k);
				}
			}
		}
		
		int cnt = 0;
		//cout << i << ": ";
		for(bool k : visited) cnt += (int)k;
		res[i] = cnt;
		mincnt = min(mincnt, cnt);
		//cout << endl;
	}
	
	// vector<int> ans(r.size(), 1);
	vector<int> ans(n,0);
	for(int i=0;i<n;i++) if(res[i] == mincnt) ans[i] = 1;
	
	return ans;
}

#ifdef LOCAL
void print(vector<int> a){
	for(int i : a) cout << i << ' ';
	cout << endl; return;
}

int main(){
	print(find_reachable({0,1,1,2},{0,0,1,1,3},{1,2,2,3,1},{0,0,1,0,2}));
	print(find_reachable({0,1,1,2,2,1,2},{0,0,1,1,2,3,3,4,4,5},{1,2,2,3,3,4,5,5,6,6},{0,0,1,0,0,1,2,0,2,1}));
	print(find_reachable({0,0,0},{0},{1},{0}));
	return 0;
}
#endif
