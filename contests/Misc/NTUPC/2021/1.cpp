#include <bits/stdc++.h>
using namespace std;

int main() {
  int m, n, p, q;
  cin >> m >> n >> p >> q;
  int candies = m * n;
  int wrappers = 0;
  int ate = 0;
  while (candies > 0) {
    // Eat all the candies
    ate += candies;
    // Add the wrappers
    wrappers += candies;
    // Exchange wrappers for candies
    candies = (wrappers / p) * q;
    // Excess wrappers
    wrappers %= p;
  }
  cout << ate << endl;
}