#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

int main(){
  cout << fixed << setprecision(2);
  ld a[8];
  for(int i=0;i<8;i++) cin >> a[i];
  sort(a,a+8);
  ld total = accumulate(a,a+8,0.0);
  ld ans = total;
  do {
    ld cur = total;
    if(a[0] + a[1] + a[2] >= 80 - 1e-5) cur -= a[3]/2;
    if(a[4] + a[5] + a[6] >= 80 - 1e-5) cur -= a[7]/2;
    ans = min(ans,cur);
  } while(next_permutation(a,a+8));
  cout << ans << endl;
}