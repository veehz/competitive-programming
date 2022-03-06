#include <bits/stdc++.h>
using namespace std;

#define _ << ' ' <<

string cp(string s, int n){
	// copy s for n times
	string ans = "";
	for(int i = 0; i < n; i++) ans += s;
	return ans;
}

int main(){
	string s,d,dna[4]; cin >> s >> d >> dna[0] >> dna[1] >> dna[2] >> dna[3];
	vector<int> pre[4];

	for(int i=0;i<4;i++){
		if(dna[i] == d){
			cout << i+1 << endl;
			int longest = 0;
			for(int t=1;;t++){
				string tmp = cp(s,t);
				if(d.find(tmp) != string::npos){
					longest = t;
				} else break;
			}
			cout << longest << endl;
			return 0;
		}
	}
	cout << 0 << endl << 0 << endl;
}
