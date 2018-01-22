#include <bits/stdc++.h>

using namespace std;

int n,m,adj[22];

bool check(int bit) {
    for (int i = 0; i < n; i++)
        if ((~bit & (1<<i)) && !(bit & adj[i]))
            return 0;
    int conn = 0;
    for (int i = 0; i < n; i++)
        if (bit & (1<<i)) {
            conn |= 1<<i;
            break;
        }
    bool b = 1;
    while (b) {
        b = 0;
        for (int i = 0; i < n; i++)
            if (conn & (1<<i)) {
                int before = conn;
                conn |= adj[i] & bit;
                if (conn != before)
                    b = 1;
            }
    }

    return bit == conn;
}

int main() {
    scanf("%d%d", &n, &m);
    
    if (m == n*(n-1)/2) {
        printf("0\n");
        return 0;
    }

    memset(adj, 0, sizeof adj);
    while (m--) {
        int u,v; scanf("%d%d", &u, &v); u--; v--;
        adj[u] |= 1<<v;
        adj[v] |= 1<<u;
    }

    int h = 10000;
    int ans = 0;
    for (int i = 0; i < (1<<n); i++)
        if (__builtin_popcount(i) < h && check(i)) {
            h = __builtin_popcount(i);
            ans = i;
        }
    printf("%d\n", h);
    for (int i = 0; i < n; i++)
        if (ans & (1<<i)) {
            printf("%d", i + 1);
            if (--h)
                printf(" ");
        }
    printf("\n");

    return 0;
}