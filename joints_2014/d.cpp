#include <bits/stdc++.h>

using namespace std;

int n,m;
long long c[51][51];

int main(void)
{
	c[1][0] = c[1][1] = 1;
	for (int i = 2; i <= 50; i++)
		for (int j = 0; j <= i; j++)
			if (j == 0 || j == i) c[i][j] = 1; else c[i][j] = c[i-1][j-1] + c[i-1][j];
			
	scanf("%d%d", &n, &m);
	printf("%lld\n", c[n-m][m]);
	return 0;
}
