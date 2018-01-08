#include <bits/stdc++.h>

using namespace std;

int n;
long long l;
pair<long long,long long> c[30];

bool cmp(pair<int,int> a, pair<int,int> b) {
    if (a.second < b.second)
        return a.first * (1LL<<(b.second-a.second)) < b.first;
    else 
        return b.first * (1LL<<(a.second-b.second)) > a.first;
}

long long solve(int x, long long remainder) {
    if (remainder <= 0) return 0;
    if (x >= n - 1)
        return ((remainder + (1LL<<c[x].second) - 1) / (1LL<<c[x].second)) * c[x].first;
    long long r = remainder / (1LL<<c[x].second);
    remainder %= 1LL<<c[x].second;
    if (remainder == 0)
        return r * c[x].first;
    return min(r*c[x].first + solve(x+1, remainder), (r+1)*c[x].first);
}

int main() {
    scanf("%d%lld", &n, &l);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &c[i].first);
        c[i].second = i;
    }
    sort(c, c + n, cmp);

    // for (int i = 0; i < n; i++)
    //     printf("%d %d\n", c[i].first, c[i].second);
    printf("%lld\n", solve(0, l));
}