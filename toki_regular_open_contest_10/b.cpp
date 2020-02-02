#include <bits/stdc++.h>

using namespace std;

int n,m,p;
long long a[1000][1000],pp[1000][1000];

int main() {
	scanf("%d%d%d", &n, &m, &p);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%lld", &a[i][j]);

	memset(pp, 0, sizeof pp);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			pp[i][j] = (i > 0 ? pp[i-1][j] : 0) + (j > 0 ? pp[i][j-1] : 0) - (i > 0 && j > 0 ? pp[i-1][j-1] : 0);
			long long curr = pp[i][j] - (i >= p ? pp[i-p][j] : 0) - (j >= p ? pp[i][j-p] : 0) + (i >= p && j >= p ? pp[i-p][j-p] : 0);
			long long s = i < n-p+1 && j < m-p+1 ? a[i][j] - curr : 0;
			if (s < 0 || s + curr != a[i][j]) {
				printf("TIDAK\n");
				return 0;
			}
			pp[i][j] += s;
		}
	printf("YA\n");
	return 0;
}
