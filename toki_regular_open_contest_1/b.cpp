#include <bits/stdc++.h>

using namespace std;

int n,r,v,w,m;

int main() {
    scanf("%d%d%d", &n, &r, &v);
    m = 2000000000;
    while (n--) {
        scanf("%d", &w);
        m = min(m, abs(w-v));
    }
    if (m == 0)
        printf("-1\n");
    else
        printf("%.10lf\n", (float) r/m);
    return 0;
}