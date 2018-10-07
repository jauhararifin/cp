#include <bits/stdc++.h>

using namespace std;

int n,m,a[100000];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    sort(a, a + n);

    long long m1 = 0;
    for (int i = 0; i < min(m, n); i++)
        m1 += 1LL * a[i];
    
    long long m2 = 0;
    int d = n / m;
    int e = n % m;
    for (int i = 0; i < n;) {
        m2 += a[i];
        if (e > 0) {
            i += d + 1;
            e--;
        } else {
            if (d == 0)
                break;
            i += d;
        }
    }

    printf("%lld %lld\n", m1, m2);

    return 0;
}