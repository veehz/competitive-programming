#ifdef LOCAL
#include "all.h"
#else
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#endif
using namespace std;
using namespace __gnu_pbds;
#include "dna.h"

struct segtree{
	int _n; vector<int> t;
	int e() { return 0; }
	int op(int a, int b) { return a+b; }
	segtree(int n){
		_n = n;
		t.assign(4*n, e());
	}
	int query(int l, int r, int v=1, int tl=0, int tr=-1){
		if(tr==-1) tr = _n-1;
		if(tl > tr) return e();
		if(tl == l && tr == r){
			return t[v];
		}
		int tm = (tl+tr)/2;
		return op( query(l,min(tm,r),2*v,tl,tm), query(max(l,tm+1),r,2*v+1,tm+1,tr) );
	}
	void update(int pos, int val, int v=1, int tl=0, int tr=-1){
		if(tr==-1) tr = _n-1;
		if(tl==tr){
			t[v] = val;
		} else {
			int tm = (tl+tr)/2;
			if(pos <= tm) update(pos,val,2*v,tl,tm);
			else update(pos, val, 2*v+1, tm+1, tr);
			t[v] = op(t[2*v],t[2*v+1]);
		}
	}
};

string a,b;
int n;

vector<int> cnta[3], cntb[3]; // A,T,C
vector<int> trans[6]; // AT,TA,AC,CA,TC,CT

const int A=0, T=1, C=2;
unordered_map<char,int> mp = {{'A',A},{'T',T},{'C',C}};
void init(string X, string Y) {
	n=X.size();
	a=X, b=Y;
	for(int i=0;i<3;i++){ cnta[i].assign(n, 0); cntb[i].assign(n, 0); }
	for(int i=0;i<6;i++) trans[i].assign(n, 0);
	int c1,c2;
	for(int i=0;i<n;i++){
		c1 = mp[X[i]]; c2 = mp[Y[i]];
		cnta[c1][i] = 1;
		cntb[c2][i] = 1;
		if(c1==0 && c2==1) trans[0][i]++;
		else if(c1==1 && c2==0) trans[1][i]++;
		else if(c1==0 && c2==2) trans[2][i]++;
		else if(c1==2 && c2==0) trans[3][i]++;
		else if(c1==1 && c2==2) trans[4][i]++;
		else if(c1==2 && c2==1) trans[5][i]++;
	}
	// prefix sum
	for(int i=1;i<n;i++){
		for(int j=0;j<3;j++){
			cnta[j][i] += cnta[j][i-1];
			cntb[j][i] += cntb[j][i-1];
		}
		for(int j=0;j<6;j++){
			trans[j][i] += trans[j][i-1];
		}
	}
}

int get_distance(int x, int y) {
	for(int i=0;i<3;i++){
		if(cnta[i][y] - (x==0?0:cnta[i][x-1]) !=  cntb[i][y] - (x==0?0:cntb[i][x-1])) return -1; 
	}
	int cnt = 0;
	int q[6];
	for(int i=0;i<6;i++) q[i] = trans[i][y] - (x==0?0:trans[i][x-1]);
	cnt  = min(q[0], q[1]) + min(q[2], q[3]) + min(q[4], q[5]);
	cnt += abs(q[0] - q[1])*2;
	return cnt;
}

#ifdef LOCAL
int main(){
	init("ATACAT","ACTATA");
	cout << get_distance(1,3) << endl;
	cout << get_distance(4,5) << endl;
	cout << get_distance(3,5) << endl;
}
#endif
