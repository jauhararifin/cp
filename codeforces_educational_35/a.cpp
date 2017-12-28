#include <bits/stdc++.h>

using namespace std;

int a[200000];

int main() {
    int n; scanf("%d", &n);
    int mi = 2000000000;
    for (int i = 0; i < n; i++)
        scanf("%d", a + i), mi = min(mi, a[i]);
    int ans = 2000000000;
    int last = -1;
    for (int i = 0; i < n; i++)
        if (a[i] == mi) {
            if (last == -1) {
                last = i;
                continue;
            }
            ans = min(ans, i - last);
            last = i;
        }
    printf("%d\n", ans);
    return 0;
}