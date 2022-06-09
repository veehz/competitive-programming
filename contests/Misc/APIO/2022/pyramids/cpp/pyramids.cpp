#include "pyramids.h"
#include <vector>
using namespace std;

vector<long long> prea, preb;
void init(vector<int> a,vector<int> b)
{
	prea.resize(a.size()+1);
	preb.resize(b.size()+1);
	prea[0] = 0;
	preb[0] = 0;
	for(int i = 1;i<=a.size();i++)
		prea[i] = prea[i-1]+a[i-1];
	for(int i = 1;i<=b.size();i++)
		preb[i] = preb[i-1]+b[i-1];
}

bool can_convert(int l1,int r1,int l2,int r2)
{
	return prea[r1+1]-prea[l1]==preb[r2+1]-preb[l2];
}