#include <bits/stdc++.h>

using namespace std;

int n,m,a[20000],b[20000],h;

int main() {
    while (1) {
        scanf("%d%d", &n, &m);
        if (n == 0 && m == 0) break;
        for (int i = 0; i < n; i++) scanf("%d", a + i);
        for (int i = 0; i < m; i++) scanf("%d", b + i);
        sort(a, a + n); sort(b, b + m);
        int i = 0, j = 0;
        h = 0;
        while (i < n) {
            if (j >= m) break;
            if (b[j] >= a[i]) {
                i++;
                h += b[j];
            }
            j++;
        }
        if (i < n) printf("Loowater is doomed!\n");
        else printf("%d\n", h);
    }
    return 0;
}