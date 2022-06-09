#ifdef LOCAL
#include "all.h"
#else
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#endif
#include "candies.h"

using namespace std;
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;

typedef long long ll;

struct segtree {
	int _n; ll lim; vector<ll> t; // vector<bool> flag;
	ll e(){
		return 0;
	}
	segtree(int n, int l) : _n(n) {
		lim = l;
		t.assign(4*_n, e());
		// t.assign(4*_n, false);
	}
	void dis(int v, ll val){
		if(val < 0){
			t[v] = max(0LL, t[v] + val);
		} else {
			t[v] = min(lim, t[v] + val);
		}
	}
	void push(int v){
		if(2*v >= 4*_n) assert(false);
		//cout << v << ' ' << t[v] << ' ' << t[2*v] << ' ' << t[2*v+1] << endl;
		dis(2*v, t[v]);
		dis(2*v+1, t[v]);
		t[v] = 0;
	}
	void update(int l, int r, ll val, int v=1, int tl=0, int tr=-1){
		if(tr==-1) tr = _n-1;
		if(l > r) return;
		if(tl >= l && tr <= r){
			dis(v, val);
		} else {
			push(v);
			int tm = (tl+tr)/2;
			update(l, min(tm,r), val, 2*v, tl, tm);
			update(max(tm+1,l), r, val, 2*v+1, tm+1, tr);
		}
		/*if(v == 1){
			for(int k : t) cout << k << ' ';
			cout << endl;
		}*/
	}
	ll query(int pos, int v=1, int tl=0, int tr=-1){
		if(tr==-1) tr = _n-1;
		if(tl==tr) return t[v];
		push(v);
		int tm = (tl+tr)/2;
		if(pos <= tm) return query(pos, 2*v, tl, tm);
		else return query(pos, 2*v+1, tm+1, tr);
	}
};

vector<int> distribute_candies(vector<int> c, vector<int> l, vector<int> r, vector<int> v) {
    int n = c.size();
	segtree seg(n, c[0]);
	for(int i=0;i<(int)l.size();i++){
		seg.update(l[i], r[i], v[i]);
	}
	vector<int> ans(n);
	for(int i=0;i<n;i++) ans[i] = seg.query(i);
    return ans;
}

int main(){
}
