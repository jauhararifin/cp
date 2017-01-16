#include <bits/stdc++.h>

using namespace std;

int t,n,s,p,k[1000],v[1000],dp[1000][1001],dpp[1001];

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%d", &n, &s, &p);
		for (int i = 0; i < n-1; i++) scanf("%d%d", k + i, v + i);
		
		memset(dp, -1, sizeof dp);
		memset(dpp, -1, sizeof dpp);
		for (int i = 0; i <= s; i++) dp[0][i] = 0;
		for (int i = 0; i < s-p+1; i++) dpp[i] = 0;
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < s-p+1; j++) dp[i][j] = dpp[j];
			for (int j = k[i-1]; j <= s; j++)
				if (dp[i-1][j] > -1)
					dp[i][j-k[i-1]] = max(dp[i][j-k[i-1]], dp[i-1][j] + v[i-1]);
			for (int j = 0; j < s-p+1; j++) dpp[j] = max(dpp[j],dp[i][j+p]);
		}
					
		int h = -1;
		for (int i = 0; i <= s; i++)
			if (dp[n-1][i] > -1)
				h = max(h, dp[n-1][i]);
				
		printf("%d\n", h);
	}
	return 0;
}
