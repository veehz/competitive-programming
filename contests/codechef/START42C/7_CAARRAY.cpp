#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;
typedef long double ld;

bool solve(int n) {
  if (n == 3) {
    cout << "2 3 6" << endl;
    return true;
  }

  if (n == 4) {
    cout << "4 24 10 15" << endl;
    return true;
  }

  if (n == 5) {
    cout << "12 10 3 4 5" << endl;
    return true;
  }

  if (n == 6) {
    cout << "720 2 3 4 5 6" << endl;
    return true;
  }

  if (n == 9) {
    cout << "362880 2 3 4 5 6 7 8 9" << endl;
    return true;
  }

  int start = (n + 2) / 3;
  int end = n / 2;

  vector<ll> extra;
  ll l = end + 1;
  ll r = n;
  for (int i = l; i <= r; i+=2) {
    extra.pb(i * (i + 1));
  }
  for (int i = 0; i < extra.size(); i++) {
    cout << extra[i] << " ";
  }
  for (int i = start; i <= n; i++) {
    cout << i << " ";
  }
  if (!(extra.size() + n - start + 1 <= n)) return false;
  for (int i = 0; i < start - 1 - extra.size(); i++) cout << 1 << ' ';
  cout << endl;
  return true;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    solve(n);
  }
}
