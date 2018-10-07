#include <bits/stdc++.h>

using namespace std;

int n,a[100],x,y;
char sx[100],sy[100];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    scanf("%d%s", &x, &sx);
    scanf("%d%s", &y, &sy);
    x--; y--;

    int ns = 0;
    int er = 0;
    for (int i = 0; i < n; i++) {
        if ((i <= x && strcmp(sx, "left") == 0) || (i >= x && strcmp(sx, "right") == 0))
            ns += a[i];
        if (a[i] == 0 && ((i <= y && strcmp(sy, "left") == 0) || (i >= y && strcmp(sy, "right") == 0)))
            er++;
    }
    printf("%d %d\n", ns, er);

    return 0;
}