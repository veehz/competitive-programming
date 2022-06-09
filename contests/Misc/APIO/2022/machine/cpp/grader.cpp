#include <bits/stdc++.h>

#include "machine.h"

using namespace std;

static int n, x;
static int qs, mx;
static vector<int> p;
static void WA(string s) {
  cout << "WA: " << s << endl;
  exit(0);
}

vector<int> use_machine(vector<int> v) {
  if ((int)v.size() != n) WA("size of queried array is not n");
  vector<int> ret;
  qs++;
  for (int i = 0; i < n; i++) {
    ret.push_back(v[p[i]] ^ x);
    mx = max(mx, v[i]);
  }
  return ret;
}

int main() {
  int t;
  assert(1 == scanf("%d", &t));
  bool ok[6] = {1, 1, 1, 1, 1, 1};
  while (t--) {
    assert(2 == scanf("%d %d", &n, &x));
    p = vector<int>(n);
    for (int i = 0; i < n; i++) assert(1 == scanf("%d", &p[i]));
    vector<int> ret = guess_permutation(n);
    if ((int)ret.size() != n) WA("size of answer is not n");
    for (int i = 0; i < n; i++)
      if (ret[i] != p[i]) WA("Invalid guess");
    printf("OK: %d %d\n", qs, mx);

    if (qs > 129 || mx > 32678) ok[0] = false;
    if (qs > 2 || mx > 32678) ok[1] = false;
	if(qs > 1 || mx > 32678) ok[2] = false;
	if(qs > 1 || mx > 2*n) ok[3] = false;
	if(qs > 1 || mx > n+2){
		if(qs%2==1) ok[4] = false;
		ok[5] = false;
	}

    mx = 0;
    qs = 0;
  }

  for (int i = 0; i < 6; i++){
	  cout << i << ": " << ok[i] << endl;
  }
}