#include <bits/stdc++.h>

using namespace std;

int n,k,a[1001];

int main() {
    scanf("%d%d", &n, &k);
    memset(a, 0, sizeof a);
    for (int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        a[x]++;
    }
    int o = 0;
    for (int i = 1; i <= k; i++)
        o += a[i] % 2;
    printf("%d\n", n - o / 2);
    return 0;
}