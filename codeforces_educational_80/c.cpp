#include <bits/stdc++.h>

using namespace std;

const long long mod = 1000000007;

int n,m;
long long dp[11][1001];

int main() {
	int n,m; scanf("%d%d", &n, &m);
	if (m == 1) {
		printf("%lld\n", ((long long) n* (long long) (n+1))/2);
		return 0;
	}

	for (int i = 1; i <= n; i++)
		dp[1][i] = i;
	for (int i = 2; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			dp[i][j] = 0;
			for (int k = 1; k <= j; k++)
				dp[i][j] = (dp[i][j] + dp[i-1][k]) % mod;
		}
	}

	// for (int i = 1; i <= m; i++)
	//   for (int j = 1; j <= n; j++)
	//     printf("n=%lld m=%lld ---> %lld\n", j, i, dp[i][j]);

	long long h = 0;
	for (int i = 1; i <= n; i++)
		h = (h + (dp[m-1][i] * dp[m][n-i+1]) % mod) % mod;
	printf("%lld\n", h);

	return 0;
}
