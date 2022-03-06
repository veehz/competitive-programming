#include <bits/stdc++.h>
using namespace std;

int main(){
  vector<string> v;
  set<string> res;
  string s;
  while(!cin.eof()){
    cin >> s;
    if(s.empty()) break;
    v.push_back(s);
  }
  for(auto now : v){
    s.clear();
    for(auto c : now){
      if(isalpha(c)) s += toupper(c);
      if(c == '\'') s += '\'';
    }
    if(!s.empty()) res.insert(s);
  }
  cout << res.size() << endl;
  for(auto now : res) cout << now << endl;
}
