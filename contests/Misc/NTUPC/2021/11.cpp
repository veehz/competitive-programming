#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<vector<int>> p(17);

int dfs(int cur_2 /* need to start from cur_2 */, int cur_3 /* max */, ll N){
  int total = 0;
  for(int i=cur_2;i<(int)p.size();i++){
    for(int j=0;j<(int)p[i].size();j++){
      if(p[i][j] >= cur_3) break;
      ll cur = pow(2,i) * pow(3,p[i][j]);
      if(cur == N) total++;
      else if(cur < N)
        total += dfs(i+1,p[i][j],N - pow(2,i)*pow(3,p[i][j]));
    }
  }
  return total;
}

int main(){
  // see how many 2^a 3^b is within 1e5
  for(ll a = 0; a <= 16; a++){
    for(ll b = 0; b <= 20; b++){
      ll n = pow(2, a) * pow(3, b);
      if(n <= 1e5){
        p[a].push_back(b);
      }
    }
  }
  int n; cin >> n;
  cout << dfs(0,1e9,n) << endl;
}