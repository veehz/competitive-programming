#include <bits/stdc++.h>
using namespace std;

int main(){
	cout << fixed << setprecision(2);
	int n; cin >> n;
	vector<double> a(n);
	for(int i=0;i<n;i++){
		string s; cin >> s;
		if(s != "#") a[i] = stod(s);
		else a[i] = -1;
	}

	double fr = a[0];
	int hc = 0;
	for(int i=0;i<n;i++){
		if(a[i] == -1){
			hc++;
		} else {
			if(hc){
				double each = (a[i] - fr) / (hc + 1);
				// print the missing values
				for(int j=0;j<hc;j++){
					cout << fr + each * (j + 1) + (double)(0.0001) << endl;
				}
				hc = 0;
			}
			fr = a[i];
		}
	}
}
