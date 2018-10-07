#include <bits/stdc++.h>

using namespace std;

int n,a[100000];
int superb[100000][10], great[100000][10];
int good[100000][10][3];
int p,q,r;

int main() {
    scanf("%d", &n); for (int i = 0; i < n; i++) scanf("%d", a + i);

    // superb left
    for (int i = 0; i < 10; i++)
        superb[0][i] = (a[0] == i ? 0 : 1);
    for (int i = 1; i < n; i++)
        for (int j = 0; j < 10; j++)
            superb[i][j] = (a[i] == j ? 0 : 1) + superb[i-1][j];
    p = n; for (int i = 0; i < 10; i++) p = min(p, superb[n-1][i]);

    // great left
    for (int i = 0; i < 10; i++)
        great[0][i] = (a[0] == i ? 0 : 1);
    for (int i = 1; i < n; i++)
        for (int j = 0; j < 10; j++) {
            great[i][j] = (a[i] == j ? 0 : 1);
            int x = max(0, j - 1);
            int y = j;
            int z = min(9, j + 1);
            great[i][j] += min(min(great[i-1][x], great[i-1][y]), great[i-1][z]);
        }
    q = n; for (int i = 0; i < 10; i++) q = min(q, great[n-1][i]);

    for (int i = 0; i < 10; i++) {
        good[0][i][0] = (a[0] == i ? 0 : 1);
        good[0][i][1] = good[0][i][2] = n;
    }

    for (int i = 1; i < n; i++) {
        int m2 = n;
        for (int j = 0; j < 10; j++)
            m2 = min(m2, good[i-1][j][2]);

        for (int j = 0; j < 10; j++) {
            good[i][j][0] = good[i][j][1] = good[i][j][2] = (a[i] == j ? 0 : 1);
            int x = max(0, j - 1);
            int y = j;
            int z = min(9, j + 1);
            good[i][j][0] += m2;
            good[i][j][1] += min(good[i-1][x][0], min(good[i-1][y][0], good[i-1][z][0]));
            good[i][j][2] += min(min(good[i-1][x][1], min(good[i-1][y][1], good[i-1][z][1])), min(good[i-1][x][2], min(good[i-1][y][2], good[i-1][z][2])));
        }
    }
    r = n; for (int i = 0; i < 10; i++) r = min(r, good[n-1][i][2]);

    printf("%d %d %d\n", r, q, p);

    return 0;
}