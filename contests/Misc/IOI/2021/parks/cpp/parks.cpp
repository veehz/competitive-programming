#include "parks.h"
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

#define F first
#define S second
#define pb push_back

#ifdef LOCAL
void build(vector<int> u,vector<int> v,vector<int> a,vector<int> b){
	u=v=a=b; v=u;
	return;
}
#endif

typedef pair<int,int> ii;

vector<int> x,y;
int n;
vector<vector<int>> edges;
map<pair<int,int>, int> taken;
vector<ii> belong;
// map<int, pair<int,int>> belong;

map<ii, int> bench_to_id;
vector<ii> id_to_bench;

vector<pair<int,int>> e;

void print(){
	int sz = 15;
	vector<vector<char>> lul(sz,vector<char>(15,' '));
	for(auto k : taken){
		if(k.S > 0){
			lul[k.F.F][k.F.S] = 'B';
		}
	}
	for(int i=0;i<n;i++){
		lul[x[i]][y[i]] = 'F';
	}
	for(int i=0;i<sz;i++){
		for(int j=0;j<sz;j++){
			cout << lul[i][j];
		}
		cout << endl;
	}
	return;
}

tuple<ii,ii> find_benches(int b){
	ii now = e[b];
	int nx = (x[now.F]+x[now.S])/2; int ny = (y[now.F] + y[now.S])/2;
	if(nx%2 == 0){ // x equal
		int nx = x[now.F]; int ny = (y[now.F] + y[now.S])/2;
		return {{nx+1,ny}, {nx-1,ny}};
	} else {
		return {{nx,ny+1}, {nx,ny-1}};
	}
}

vector<vector<int>> ce;
vector<vector<int>> cb;

vector<int> edge_connect;
vector<int> bench_connect;

void travel_en(int en){
	for(int bn : ce[en]){
		if(bench_connect[bn] >= 0) continue;
		edge_connect[en] = bn;
		bench_connect[bn] = en;
		for(int een : cb[bn]) if(edge_connect[een] < 0) travel_en(een);
	}
}

void travel(int k){ // bench k
	// if(bench_connect[bn] >= 0) return;
	for(int en : cb[k]){
		if(edge_connect[en] >= 0) continue;
		edge_connect[en] = k;
		bench_connect[k] = en;
		for(int bn : ce[en]) if(bench_connect[bn] < 0) travel(bn);
		break;
	}
	for(int en : cb[k]){
		if(edge_connect[en] < 0) travel_en(en);
	}
}

void change(int i){
	pair<int,int> c1,c2;
	tie(c1,c2) = find_benches(i);
	// which bench is mine
	if(c1 != belong[i]) swap(c1,c2);
	// now c2 is mine
	
	int prevowner = taken[c2] - 1;
	
	belong[i] = c2;
	taken[c2] = i+1;
	
	if(prevowner >= 0){
		change(prevowner);
	}
}

int dx[4] = {0,0,2,-2};
int dy[4] = {2,-2,0,0};
int construct_roads(vector<int> X, vector<int> Y) {
    // subtask 4/5
    x=X,y=Y;
    taken.clear();
    belong.clear();
    e.clear();
    n = x.size();
    edges.assign(n,{});
	map<pair<int,int>,int> exist;
	vector<bool> visited(n,false);
	for(int i=0;i<n;i++) exist[{x[i],y[i]}] = i+1;
	queue<int> q;
	q.push(0);
	visited[0] = true;
	while(!q.empty()){
		int s = q.front(); q.pop();
		for(int i=0;i<4;i++){
			int nx = x[s] + dx[i], ny = y[s] + dy[i];
			int res = exist[{nx,ny}];
			if(res <= 0) continue;
			res--;
			if(visited[res]) continue;
			visited[res] = true;
			e.pb({s,res});
			// add edge between s, res;
			q.push(res);
		}
	}
	for(bool k : visited){
		if(!k) return 0;
	}
	int m = e.size();
	//for(auto k : e) cout << k.F << " " << k.S << endl;
	
	set<ii> set_of_benches;
	ii c1,c2;
	for(int i=0;i<m;i++){
		tie(c1,c2) = find_benches(i);
		set_of_benches.insert(c1);
		set_of_benches.insert(c2);
	}
	int sb = set_of_benches.size();
	id_to_bench.assign(sb, {0,0});
	{
		int i=0;
		for(auto k : set_of_benches){
			// cout << k.F << ' ' << k.S << endl;
			id_to_bench[i] = k;
			bench_to_id[k] = i;
			i++;
		}
	}
	// edges: 0 to m-1
	// benches : 0 to sb-1
	ce.assign(m, {});
	cb.assign(sb,{});
	bench_connect.assign(sb, -1);
	edge_connect.assign(m, -1);
	int i1,i2;
	for(int i=0;i<m;i++){
		tie(c1,c2) = find_benches(i);
		i1 = bench_to_id[c1];
		i2 = bench_to_id[c2];
		ce[i].pb(i1); ce[i].pb(i2);
		cb[i1].pb(i); cb[i2].pb(i);
	}
	
	for(int i=0;i<sb;i++){
		if(bench_connect[i] >= 0) continue;
		travel(i);
	}
	
	/* // THIS ONE TAKES TOO LONG
	// assign benches
	belong.assign(m,{0,0});
	for(int i=0;i<m;i++){
		change(i);
	}
	*/
	
	// print();
	
	vector<int> u(m), v(m), a(m), b(m); 
	for(int i=0;i<m;i++){
		u[i] = e[i].F;
		v[i] = e[i].S;
		ii QQ = id_to_bench[edge_connect[i]];
		a[i] = QQ.F;
		b[i] = QQ.S;
	}
	build(u,v,a,b);
	return 1;
}

#ifdef LOCAL
int main(){
	cout << construct_roads({3},{6}) << endl;
	cout << construct_roads({2,4,4,4,6,8,8,10,10,10,8,6,6},{6,6,8,4,6,6,8,6,4,2,2,2,4}) << endl;
	cout << construct_roads({4,4,6,4,2},{4,6,4,2,4}) << endl;
	cout << construct_roads({2,4},{2,6}) << endl;
	
	return 0;
}
#endif
