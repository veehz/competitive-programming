#include "treasure.h"

#include <bits/stdc++.h>
using namespace std;

void split(string& x, string& sid, vector<int>& res) {
  int k = min(4, (int)x.size());
  res.push_back(stoi(sid + x.substr(0, k)));
  x = x.substr(k);
  if (x.empty()) return;

  k = min(3, (int)x.size());
  res.push_back(stoi(sid + x.substr(0, k)));
  x = x.substr(k);
  if (x.empty()) return;

  k = min(2, (int)x.size());
  res.push_back(stoi(sid + x.substr(0, k)));
  x = x.substr(k);
  if (x.empty()) return;
}

vector<int> encode(vector<int> x, vector<int> y) {
  vector<int> res;

  for (int i = 0; i < x.size(); i++) {
    string sid = to_string(10000 + 2 * i);
    string sx = to_string(x[i]);
    split(sx, sid, res);

    sid = to_string(10000 + 2 * i + 1);
    sx = to_string(y[i]);
    split(sx, sid, res);
  }

  return res;
}

vector<int> decode(vector<int> e) {
  vector<int> res;
  vector<vector<string>> m(e.size());

  for (auto& k : e) {
    string s = to_string(k);
    int id = stoi(s.substr(0, 5));
    m[id-10000].push_back(s.substr(5));
  }

  for (int i = 0; i < m.size(); i++) {
    if (m[i].size() == 0) break;
    auto& v = m[i];
    sort(v.begin(), v.end(),
         [&](string& a, string& b) { return a.size() > b.size(); });
    string s = v[0];
    for (int i = 1; i < v.size(); i++) s += v[i];
    res.push_back(stoi(s));
  }

  return res;
}
