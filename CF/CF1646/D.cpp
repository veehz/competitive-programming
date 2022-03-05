#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;

vector<vector<int>> e;
vector<int> par;
vector<set<int>> get_from;

void dfs(int r, int p){
	par[r] = p;
	for(int k : e[r]){
		if(k == p) continue;
		dfs(k,r);
	}
}

void solve() {
	return;
}

pair<int,int> getNR(int r);

vector<pair<int,int>> getR_dp;
pair<int,int> getR(int r){
	if(getR_dp[r].first >= 0) return getR_dp[r];
	int cnt = 1;
	int val = 0;
	for(auto k : e[r]){
		if(k == par[r]) continue;
		// self is R, add 1
		val++;
		auto [nc,nv] = getNR(k);
		cnt += nc;
		val += nv;
	}
	return getR_dp[r] = {cnt,val};
}

vector<pair<int,int>> getNR_dp;
pair<int,int> getNR(int r){
	if(getNR_dp[r].first >= 0) return getNR_dp[r];
	int cnt = 0;
	int val = 1;
	for(auto k : e[r]){
		if(k == par[r]) continue;
		// self gives, add 1
		pair<int,int> ifR = getR(k);
		pair<int,int> ifNR = getNR(k);
		if(ifR.first == ifNR.first){
			if(ifR.second + 1 < ifNR.second){
				// take R
				cnt += ifR.first;
				val += ifR.second + 1;
			} else {
				// take NR
				get_from[r].insert(k);
				cnt += ifNR.first;
				val += ifNR.second;
			}
		} else if(ifR.first > ifNR.first){
			// take R
				cnt += ifR.first;
				val += ifR.second + 1;
		} else {
			// take NR
				get_from[r].insert(k);
				cnt += ifNR.first;
				val += ifNR.second;
		}
	}
	return getNR_dp[r] = {cnt,val};
}

vector<int> reconstruct;
void drawNR(int r);

void drawR(int r){
	for(auto k : e[r]) if(k != par[r]) drawNR(k);
	reconstruct[r] = e[r].size();
}

void drawNR(int r){
	for(auto k : e[r]){
		if(k == par[r]) continue;
		if(get_from[r].count(k)) drawNR(k);
		else drawR(k);
	}
}

pair<int,int> count(vector<int>& x){
	int n = e.size();
	int cnt = 0;
	for(int i=0;i<n;i++){
		int now = 0;
		for(auto k : e[i]) now += x[k];
		if(now == x[i]) cnt++;
	}
	return {cnt,accumulate(x.begin(),x.end(),0)};
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	int n; cin >> n;
	e.assign(n,{}); par.assign(n,0);
	get_from.assign(n,{});
	getR_dp.assign(n,{-1,-1});
	getNR_dp.assign(n,{-1,-1});
	for(int i=0;i<n-1;i++){
		int a,b; cin >> a >> b;
		a--; b--;
		e[a].pb(b);
		e[b].pb(a);
	}
	dfs(0,0);
	
	// cout << max(getR(0).first,getNR(0).first) << endl;
	// cout << get_from << endl;
	getR(0);
	getNR(0);
	
	reconstruct.assign(n,1);
	drawR(0);
	auto [r,rv] = count(reconstruct);
	
	reconstruct.assign(n,1);
	drawNR(0);
	auto [nr,nrv] = count(reconstruct);
	
	if(r == nr){
		if(nrv <= rv){
			cout << nr << ' ' << nrv << endl;
		} else {
			reconstruct.assign(n,1);
			drawR(0);
			cout << r << ' ' << rv << endl;
		}
	} else if(r > nr){
		reconstruct.assign(n,1);
		drawR(0);
		cout << r << ' ' << rv << endl;
	} else {
		cout << nr << ' ' << nrv << endl;
	}
	
	for(int i=0;i<n;i++) cout << reconstruct[i] << ' ';
	cout << endl;
}
