#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;
typedef long double ld;

int solve(int a, int b){
	if(a%3==0 || b%3==0) return 0;

	queue<pair<pair<int,int>,int>> q; q.push({{a,b},0});
	while(!q.empty()){
		auto [x,d] = q.front();
		auto [a,b] = x;
		q.pop();
		if(abs(a-b)%3==0) return d+1;
		q.push({{abs(a-b),b},d+1});
		q.push({{a,abs(a-b)},d+1});
	}
}

int main() {
  int t;
  cin >> t;
  while (t--){
	  int a,b; cin >> a >> b;
	  cout << solve(a,b) << endl;
  }
}
