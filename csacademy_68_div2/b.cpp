#include <bits/stdc++.h>

using namespace std;

int n,m,k;

int main() {
    scanf("%d%d%d", &n, &m, &k); n++; m++;
    if (k == 1) {
        printf("%d\n", n * m);
        return 0;
    }

    int ans = 0;
    for (int x1 = 1; x1 <= n; x1++)
        for (int y1 = 1; y1 <= m; y1++)
            for (int x2 = 1; x2 <= n; x2++)
                for (int y2 = 1; y2 <= m; y2++)
                    if (1 + __gcd(abs(y2-y1), abs(x2-x1)) == k) {
                        // printf("%d %d, %d %d\n", x1, y1, x2, y2);
                        ans++;
                    }
    printf("%d\n", ans/2);

    return 0;
}