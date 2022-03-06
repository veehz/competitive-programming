#include <bits/stdc++.h>
using namespace std;

map<string, double> growth_factor = {
    {"American Beech", 6},       {"Basswood", 3},
    {"Common Horsechestnut", 8}, {"Dogwood", 7},
    {"European White Birch", 5}, {"White Fir", 7.5}};

typedef long double ld;
const ld PI = 3.141592;
int main() {
  cout << fixed << setprecision(1);
  ld m;
  cin >> m;
  if (m - floor(m) != 0 || m <= 0) {
    cout
        << "You must specify a positive integer number for the number of trees!"
        << endl;
    return 0;
  }

  int n = m;
  ld circum;
  string tree;
  for (int i = 0; i < n; i++) {
    cin >> circum;
    getline(cin, tree);  // remove newline
    getline(cin, tree);  // read tree name
    if (circum <= 0) {
      cout << "The circumference for " << tree << " must be greater than 0!"
           << endl;
      continue;
    }
    if (!growth_factor.count(tree)) {
      cout << "Species entered is not available!" << endl;
      continue;
    }
    cout << tree << " : " << circum << " : "
         << circum / PI * growth_factor[tree] << endl;
  }
}
