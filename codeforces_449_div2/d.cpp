#include <bits/stdc++.h>

using namespace std;

int n,m,c,x,a[2000],remaining;

int main() {
    scanf("%d%d%d", &n, &m, &c);
    memset(a, -1, sizeof a);

    remaining = n;
    while (m-- && remaining) {
        scanf("%d", &x);
        if (x <= c/2) {
            for (int i = 0; i < n; i++)
                if (a[i] < 0 || a[i] > x) {
                    if (a[i] < 0) remaining--;
                    printf("%d\n", i + 1);
                    a[i] = x;
                    fflush(stdout);
                    break;
                }
        } else {
            for (int i = n - 1; i >= 0; i--)
                if (a[i] < 0 || a[i] < x) {
                    if (a[i] < 0) remaining--;
                    printf("%d\n", i + 1);
                    a[i] = x;
                    fflush(stdout);
                    break;
                }
        }
    }

    return 0;
}