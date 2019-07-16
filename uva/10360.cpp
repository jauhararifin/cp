#include <bits/stdc++.h>

using namespace std;

int t,n,d,p[1025][1025];

int main() {
    scanf("%d", &t);
    while (t--) {
        memset(p, 0, sizeof p);
        scanf("%d%d", &d, &n);
        int x,y,z; while (n--) {
            scanf("%d%d%d", &x, &y, &z);
            p[y][x] += z;
        }
        for (int i = 0; i <= 1024; i++)
            for (int j = 0; j <= 1024; j++) {
                x = j > 0 ? p[i][j-1] : 0;
                y = i > 0 ? p[i-1][j] : 0;
                z = i > 0 && j > 0 ? p[i-1][j-1] : 0;
                p[i][j] = p[i][j] + x + y - z;
            }
        x = y = z = -1;
        for (int j = 0; j <= 1024; j++)
            for (int i = 0; i <= 1024; i++) {
                int a = p[min(1024, i+d)][min(1024, j+d)];
                int b = j-d-1 >= 0 ? p[min(1024, i+d)][j-d-1] : 0;
                int c = i-d-1 >= 0 ? p[i-d-1][min(1024, j+d)] : 0;
                int e = i-d-1 >= 0 && j-d-1 >= 0 ? p[i-d-1][j-d-1] : 0;
                int r = a - b - c + e;
                if (r > z) {
                    z = r;
                    x = j;
                    y = i;
                }
            }
        printf("%d %d %d\n", x, y, z);
    }
    return 0;
}