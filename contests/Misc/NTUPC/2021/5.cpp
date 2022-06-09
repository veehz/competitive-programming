#include <bits/stdc++.h>
using namespace std;

int main() {
  string s = "abcdefgha";
  int n;
  cin >> n;
  while (n--) {
    char c, d;
    cin >> c >> d;
    int pos1, pos2;
    pos1 = s.find(c);
    pos2 = s.find(d);
    if (pos1 > pos2) swap(pos1, pos2);
    reverse(s.begin() + pos1, s.begin() + pos2 + 1);
  }
  cout << s << endl;
}
