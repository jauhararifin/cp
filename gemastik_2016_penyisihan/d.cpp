#include <bits/stdc++.h>

using namespace std;

int memo[101][101][201];
int f(int l, int b, int r) {	
	if (r > l + b) return r;
	if (l < 0 || b < 0 || r < 0 || (r == 0 && (l+b > 0))) return 1000000000;
	if (memo[l][b][r] >= 0) return memo[l][b][r];
	if (l == 0 && b == 0) return memo[l][b][r] = r;
	if ((b == 0 && l <= 4) || (b == 1 && l <= 3) || (b == 2 && l <= 2) || (b == 3 && l == 0)) return memo[l][b][r] = r > 0 ? r : 1000000000;
	
	
	int a[][3] = {{0,0,0},{0,0,1},{0,0,2},{0,0,3},{0,0,4}
				 ,{0,-1,0},{0,-1,1},{0,-1,2},{0,-1,3},{0,-2,0},{0,-2,1},{0,-2,2},{0,-3,0}
				 ,{-1,0,0},{-1,0,1},{-1,0,2},{-1,0,3},{-1,-1,0},{-1,-1,1},{-1,-1,2},{-1,-2,0},{-1,-2,1}
				 ,{-2,0,0},{-2,0,1},{-2,0,2},{-2,-1,0},{-2,-1,1}
				 ,{-3,0,0},{-3,0,1},{-4,0,0}};
	
	memo[l][b][r] = 1000000000;
	for (int i = 0; i < 30; i++)
		memo[l][b][r] = min(memo[l][b][r], 1 + f(l + a[i][0],b + a[i][1],r - 1 + a[i][2]));
	
	return memo[l][b][r];
}

int t,x,y;

int main() {
	memset(memo, -1, sizeof memo);
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &x, &y);
		if (x == 0 && y == 0) printf("%d\n", 0);
		else printf("%d\n", f(x,y,1));
	}
	return 0;
}
