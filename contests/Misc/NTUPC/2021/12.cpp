#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

struct polynomial {
  int deg = 0;
  vector<ld> a;
  polynomial() : polynomial(0) {}
  explicit polynomial(int d) {
    if (d >= 0) {
      deg = d;
      a.assign(d + 1, 0);
    }
  }
  void set(int p, ld val) { a[p] = val; }
  ld eval(ld x) {
    ld res = 0;
    for (int i = 0; i <= deg; i++) {
      res += (ld)pow(x, i) * (ld)a[i];
    }
    return res;
  }
  polynomial derivative() {
    if (!deg) return polynomial();
    polynomial res(deg - 1);
    for (int i = 0; i < deg; i++) {
      res.set(i, a[i + 1] * (i + 1));
    }
    return res;
  }
  ld newton_method(ld low, ld high) {
    /* Newton's method, there exists exactly one root between low and high */
    /* Find the root between low and high */
    /* split into 100 parts, 10000 iterations each */
    if(abs(eval(low)) < 1e-10) return low;
    if(abs(eval(high)) < 1e-10) return high;
    polynomial f = derivative();
    for(ld i = low; i <= high; i+=(high-low)/100){
      ld x = i;
      for (int j = 0; j < 1000; j++) {
        ld fx = eval(x);
        ld fpx = f.eval(x);
        x -= fx / fpx;
        if(low < x && x < high && abs(eval(x)) < 1e-10){
          return x;
        }
      }
    }
  }
};

int main() {
  cout << fixed << setprecision(6);
  int n;
  cin >> n;
  polynomial poly(n);
  ld k;
  for (int i = n; i >= 0; i--) {
    cin >> k;
    poly.set(i, k);
	// cout << k << endl;
  }
  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    ld l, h;
    cin >> l >> h;
    cout << poly.newton_method(l, h) << endl;
  }
}
