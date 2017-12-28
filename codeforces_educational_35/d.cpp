#include <bits/stdc++.h>

using namespace std;

int n,m,a[1500],p[1500][1500];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", a + i);
    memset(p, 0, sizeof p);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (a[j] > a[i])
                p[i][j]++;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            p[i][j] = p[i][j] + (j > 0 ? p[i][j-1] : 0) + (i > 0 ? p[i-1][j] : 0) - (i > 0 && j > 0 ? p[i-1][j-1] : 0);
    
    int s = p[n - 1][n - 1];
    scanf("%d", &m);
    while (m--) {
        int l,r; scanf("%d%d", &l, &r); l--; r--;
        int n = r - l + 1;
        int c = p[r][r] - (l > 0 ? p[r][l-1] : 0) - (l > 0 ? p[l-1][r] : 0) + (l > 0 ? p[l-1][l-1] : 0);
        int d = (n*(n-1))/2 - c;
        s = s - c + d;
        printf("%s\n", s & 1 ? "odd" : "even");
    }

    return 0;
}