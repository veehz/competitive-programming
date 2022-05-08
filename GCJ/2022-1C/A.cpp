/* MGod. */
#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

vector<string> split(string& s){
	// split by space
	vector<string> res;
	stringstream ss(s);
	string temp;
	while(getline(ss, temp, ' ')){
		if(temp.size()) res.pb(temp);
	}
	return res;
}

void solve() {
	int n; cin >> n;
	string all;
	getline(cin,all); // empty
	getline(cin,all);
	vector<string> ss = split(all), ss2;

	vector<bool> same(26,false);
	vector<string> sames(26,"");
	for(auto& s : ss){
		bool ok = true;
		for(auto& c : s){
			if(c != s[0]){
				ok = false; break;
			}
		}
		if(ok){
			same[s[0]-'A'] = true;
			sames[s[0]-'A'] += s;
		}
		else ss2.pb(s);
	}
	ss = ss2;

	n = ss.size();
	vector<set<int>> e(26+26);
	for(int i=0;i<n;i++){
		e[ss[i][0]-'A'].insert(i);
		e[ss[i].back()-'A' + 26].insert(i);
	}

	string last;
	for(int i=0;i<26;i++){
		if(!same[i]) continue;
		if(e[i+26].size()) { ss[*e[i+26].begin()] += sames[i]; continue; }
		if(e[i].size()) { ss[*e[i].begin()] = sames[i] + ss[*e[i].begin()]; continue; }
		last += sames[i];
	}

	while(true){
		bool done = false;
		for(int i=0;i<26;i++){
			if(e[i].size() && e[i+26].size()){
				if(*e[i].begin() == *e[i+26].begin()){
					// cout << i << ' ' << ss[*e[i].begin()] << endl;
					cout << "IMPOSSIBLE" << endl;
					return;
				}
				string ns;
				ns = ss[*e[i+26].begin()] + ss[*e[i].begin()];
				int n1 = *e[i].begin(), n2 = *e[i+26].begin();
				e[ss[n1][0]-'A'].erase(n1);
				e[ss[n2][0]-'A'].erase(n2);
				e[ss[n1].back()-'A' + 26].erase(n1);
				e[ss[n2].back()-'A' + 26].erase(n2);
				ss[n1] = ns;
				e[ss[n1][0]-'A'].insert(n1);
				e[ss[n1].back()-'A' + 26].insert(n1);
				done = true;
			}
		}
		if(!done) break;
	}

	
	for(int i=0;i<26;i++){
		if(e[i].size() > 1) {
			// for(auto& k : e[i]) cout << ss[k] << endl;
			cout << "IMPOSSIBLE" << endl;
			return;
		}
		if(e[i].size()) last += ss[*e[i].begin()];
	}

	vector<bool> f(26,false);
	f[last[0]-'A'] = true;
	for(int i=1;i<last.size();i++){
		if(f[last[i]-'A'] && last[i-1] != last[i]){
			cout << "IMPOSSIBLE" << endl;
			return;
		} else f[last[i]-'A'] = true;
	}

	cout << last << endl;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	int t; cin >> t;
	for(int i=0;i<t;i++){
		cout << "Case #" << i+1 << ": ";
		solve();
	}
}

