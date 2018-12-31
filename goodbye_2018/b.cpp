#include <bits/stdc++.h>

using namespace std;

int n,x,y,a,b,rx,ry;

int main() {
    scanf("%d", &n);
    rx = ry = 2000000000;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &x, &y);
        rx = min(x, rx);
        ry = min(y, ry);
    }
    x = y = -2000000000;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &a, &b);
        x = max(a, x);
        y = max(b, y);
    }
    printf("%d %d\n", rx + x, ry + y);
    return 0;
}