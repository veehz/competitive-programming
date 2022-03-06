#include <bits/stdc++.h>
using namespace std;

int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int main(){
	int m,n,z;
	cin >> m >> n >> z;
	vector<vector<int>> a(m+2, vector<int>(n+2, 0));
	while(z--){
		int x,y;
		cin >> x >> y;
		x++; y++;
		a[x][y] = -1;
		for(int i=0;i<8;i++){
			if(a[x+dx[i]][y+dy[i]] >= 0)
				a[x+dx[i]][y+dy[i]]++;
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j] == -1)
				cout << '*';
			else
				cout << a[i][j];
		}
		cout << endl;
	}
}
