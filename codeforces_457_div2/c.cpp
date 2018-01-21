#include <bits/stdc++.h>

using namespace std;

int n,m;
bool sv[200001];
set<int> primes;

int main() {
    memset(sv, 0, sizeof sv); sv[1] = 1;
    for (int i = 2; i <= 200000; i++)
        if (!sv[i]) {
            primes.insert(i);
            for (int j = i + i; j <= 200000; j += i)
                sv[j] = 1;
        }

    scanf("%d%d", &n, &m);
    int sp = *(primes.lower_bound(n-1));
    int ot = sp + 1;

    printf("%d %d\n", sp, sp);
    for (int i = 0; i < n - 2; i++)
        printf("%d %d %d\n", i + 1, i + 2, 1);
    printf("%d %d %d\n", n - 1, n, sp - (n - 2));
    m -= n - 1;
    int i = 0, j = 2;
    while (m--) {
        printf("%d %d %d\n", i + 1, j + 1, ot);
        j++;
        if (j >= n) {
            i++;
            j = i + 2;
        }
    }

    return 0;
}