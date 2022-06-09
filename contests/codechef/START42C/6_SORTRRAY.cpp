#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;
typedef long double ld;

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<int> b(n);
  for (int i = 0; i < n; i++) {
    int needToBe = (1 << 19) - n + i;
    b[i] = needToBe - a[i];
  }
  vector<pair<int, vector<int>>> ans;
  for (int i = 0; i < 19; i++) {
    vector<int> cur;
    for (int j = 0; j < n; j++) {
      if (b[j] & (1 << i)) cur.pb(j);
    }
    if (cur.size() > 0 && (int)cur.size() < n) ans.pb({i, cur});
  }

  cout << ans.size() << endl;
  for (auto& [x, v] : ans) {
    cout << v.size() << ' ' << (1 << x) << endl;
    for (auto& i : v) {
      cout << i + 1 << ' ';
      //   a[i] += (1 << x);
    }
    cout << endl;
  }

  //   for (int i = 0; i < n; i++) {
  // 	cout << a[i] << ' ';
  //   }
}

int main() {
  int t;
  cin >> t;
  while (t--) solve();
}
