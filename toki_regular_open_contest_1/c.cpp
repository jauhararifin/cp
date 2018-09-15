#include <bits/stdc++.h>

using namespace std;

int n,q,t[100000],x[100000];
long long y[100000],a[400001],v,h;
set<int> c;
map<int,int> zip;

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 0; i < q; i++) {
        scanf("%d%d%lld", t + i, x + i, y + i);
        if (t[i] == 1)
            c.insert(x[i]), c.insert(x[i] + 1), c.insert(x[i] - 1);
        else
            c.insert(n - x[i] + 1), c.insert(n - x[i]), c.insert(n - x[i] + 2);
    }
    int j = 0;
    for (int temp : c) {
        if (temp < 1) continue;
        if (temp > n) continue;
        zip[temp] = ++j;
    }
    for (int i = 0; i < q; i++) {
        int temp = -1;
        if (t[i] == 1)
            temp = zip[x[i]];
        else
            temp = zip[n - x[i] + 1];
        x[i] = temp;
    }
    n = j;

    // for (int i = 0; i < q; i++)
    //     printf("%d %d %d\n", t[i], x[i], y[i]);

    memset(a, 0, sizeof a);
    for (int i = 0; i < q; i++)
        if (t[i] == 1)
            a[0] += y[i], a[x[i]] -= y[i];
        else
            a[x[i]-1] -= y[i];

    // for (int i = 0; i <= n; i++)
    //     printf("%lld ", a[i]); printf("\n");

    v = 0;
    h = 0;
    for (int i = 0; i < n; i++) {
        v += a[i];
        h = max(abs(v), h);
    }
    printf("%lld\n", h);
    return 0;
}