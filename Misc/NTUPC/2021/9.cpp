#include <bits/stdc++.h>
using namespace std;

vector<string> split(string s, char c) {
    vector<string> res;
    stringstream ss(s);
    string x;
    while (getline(ss, x, c)) res.push_back(x);
    return res;
}

string timeToString(int raw_m){
  raw_m *= 5;
  // 10:00 + raw_m minutes
  int m = raw_m % 60;
  int h = raw_m / 60 + 10;
  string res = to_string(h);
  if (m < 10) res += ":0" + to_string(m);
  else res += ":" + to_string(m);
  return res;
}

int main(){
  string s; cin >> s;
  vector<string> ord = split(s,';');
  vector<string> cus;
  vector<vector<int>> num;
  for(auto ss : ord){
    cus.push_back(split(ss,'#')[0]);
    vector<string> orders = split(ss,'%');
    vector<int> res;
    for(auto k : orders){
      res.push_back(stoi(split(k,':')[1]));
    }
    sort(res.begin(),res.end(),greater<int>());
    num.push_back(res);
  }
  int chef[3] = {0,0,0};
  for(int i=0;i<(int)num.size();i++){
    int cur_max = 0;
    for(auto n : num[i]){
      sort(chef,chef+3);
      chef[0] += n;
      cur_max = max(cur_max,chef[0]);
    }
    cout << cus[i] << " can collect food at " << timeToString(cur_max) << endl;
  }
}