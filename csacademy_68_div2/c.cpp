#include <bits/stdc++.h>

using namespace std;

int n,bit[100001];
tuple<int,int,int> p[100000];
int v[100000];

bool cmp(tuple<int,int,int> a, tuple<int,int,int> b) {
    int x1, y1, x2, y2;
    tie(x1, y1, ignore) = a;
    tie(x2, y2, ignore) = b;
    return 1LL * y1 * x2 < 1LL * y2 * x1;
}

int query(int idx){
    int sum = 0;
    for (; idx > 0; idx -= (idx & -idx))
        sum += bit[idx];
    return sum;
}

int update(int idx, int v) {
    for (;idx <= 100000; idx += (idx & -idx))
        bit[idx] += v;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x,y; scanf("%d%d", &x, &y);
        p[i] = make_tuple(x,y,i);
    }
    sort(p, p + n, cmp);

    memset(bit, 0, sizeof bit);
    for (int i = 0; i < n; i++) {
        int x,y,idx; tie(x,y,idx) = p[i];
        v[idx] = query(x);
        update(x, 1);
    }
    for (int i = 0; i < n; i++)
        printf("%d\n", v[i]);
    return 0;
}