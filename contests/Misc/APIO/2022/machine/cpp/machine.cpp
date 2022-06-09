#include "machine.h"

#include <bits/stdc++.h>
using namespace std;

vector<int> guess_permutation(int n) {
  vector<int> res;
  for (int i = 0; i < n; i++) res.push_back(i);
  res[0] += 1 << (32 - __builtin_clz(n));
  res = use_machine(res);
  int sc = 0;
  for (int i = 0; i < n; i++) {
    if (res[i] & (1 << (32 - __builtin_clz(n)))) ++sc;
  }

  int rnum = 0;
  if (sc == 1) {
    for (int i = 0; i < n; i++) {
      if (res[i] & (1 << (32 - __builtin_clz(n)))) {
        rnum = i;
        break;
      }
    }
  } else {
    for (int i = 0; i < n; i++) {
      if (!(res[i] & (1 << (32 - __builtin_clz(n))))) {
        rnum = i;
        break;
      }
    }
  }

  int x = res[rnum]^(1 << (32 - __builtin_clz(n)));
  res[rnum] ^= (1 << (32 - __builtin_clz(n)));
  for (int i = 0; i < n; i++) {
	  res[i] ^= x;
  }

  return res;
}