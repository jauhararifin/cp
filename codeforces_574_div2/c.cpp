#include <bits/stdc++.h>

using namespace std;

int n;
long long a[100000],b[100000];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%I64d", a + i);
    for (int i = 0; i < n; i++) scanf("%I64d", b + i);

    long long pa = 0, pb = 0, pc = 0;
    for (int i = 0; i < n; i++) {
        long long na = max(pb + a[i], pc + a[i]);
        long long nb = max(pa + b[i], pc + b[i]);
        long long nc = max(pc, max(pa, pb));
        pa = na;
        pb = nb;
        pc = nc;
    }
    printf("%I64d\n", max(max(pa, pb), pc));

    return 0;
}