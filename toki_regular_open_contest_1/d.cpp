#include <bits/stdc++.h>

#define ll long long

using namespace std;

int n,a[100000],m;
long long sum;

long long add_zero(long long sum, int n) {
    long long nl = (long long) n;
    return (nl & 1LL ? (((nl + 1LL) >> 1LL) * nl) : ((nl >> 1LL) * (nl + 1LL))) - sum;
}

long long add_one(long long sum, int n) {
    long long nl = (long long) n;
    return (nl & 1LL ? (((nl + 1LL) >> 1LL) * (nl + 2LL)) : (((nl + 2LL) >> 1LL) * (nl + 1LL))) - sum;
}

long long add_two(long long sum, int n) {
    long long nl = (long long) n;
    return (nl & 1LL ? (((nl + 3LL) >> 1LL) * (nl + 2LL)) : (((nl + 2LL) >> 1LL) * (nl + 3LL))) - sum;
}

bool check(int m) {
    int state = 0;
    for (int i = 0; i < n; i++)
        if (state == 0) {
            if (a[i] + i < m) {
                state = m - (a[i] + i) == 1 ? 2 : 1;
            }
        } else if (state == 1) {
            if (m - (a[i] + i) <= 1) {
                state = 2;
            }
        } else if (state == 2) {
            if (a[i] + i < m) {
                return 0;
            }
        }
    if (m > n && state == 2) return 0;
    return 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", a + i);
    m = n;
    sum = 0;
    for (int i = 0; i < n; i++)
        m = max(i + a[i], m), sum += (ll) a[i];

    if (check(m)) printf("%lld\n", add_zero(sum, m));
    else if (check(m+1)) printf("%lld\n", add_one(sum, m));
    else printf("%lld\n", add_two(sum, m));
}
