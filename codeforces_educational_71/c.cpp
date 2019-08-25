#include <bits/stdc++.h>
 
using namespace std;
 
int t,n,a,b;
long long dp[200000][2];
char s[200001];
 
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &a, &b);
        scanf("%s", s);
        memset(dp, 0, sizeof dp);
        dp[0][0] = a + b + b;
        dp[0][1] = 1e14;
        for (int i = 1; i < n; i++)
            if (s[i] == '0') {
                dp[i][0] = min(dp[i-1][0] + a + b, dp[i-1][1] + a + a + b + b);
                dp[i][1] = min(dp[i-1][0] + a + a + b + b, dp[i-1][1] + b + b + a);
            } else {
                dp[i][0] = 1e14;
                dp[i][1] = min(dp[i-1][0] + a + a + b + b, dp[i-1][1] + b + b + a);
            }
        printf("%lld\n", dp[n-1][0]);
    }
    return 0;
}
