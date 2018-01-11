#include <bits/stdc++.h>

using namespace std;

typedef struct {
    int op,l,r,x,y;
} query;

int n,m,seed,vmax,a[100000];
query qs[100000];

int rnd() {
    int ret = seed;
    seed = (1LL * seed * 7LL + 13LL) % 1000000007LL;
    return ret;
}

long long get_num(map<int,long long>& mp, int i) {
    auto it = mp.lower_bound(i);
    if (it == mp.end() || it->first > i)
        it--;
    return it->second;
}

long long pow(long long a, int b, int mod) {
    if (b == 0) return 1LL;
    if (b == 1) return a % mod;
    long long c = pow(a,b/2,mod) % mod;
    if (b & 1) return (((c * c) % mod) * (a % mod)) % mod;
    return (c * c) % mod;
}

void debug_range(map<int,long long>& mp) {
    for (auto i = mp.begin(); i != mp.end(); i++)
        printf("(%d %lld) ", i->first, i->second);
    printf("\n");
}

int main() {
    scanf("%d%d%d%d", &n, &m, &seed, &vmax);
    for (int i = 0; i < n; i++)
        a[i] = (rnd() % vmax) + 1;
    for (int i = 0; i < m; i++) {
        qs[i].op = (rnd() % 4) + 1;
        qs[i].l = (rnd() % n) + 1 - 1;
        qs[i].r = (rnd() % n) + 1 - 1;
        if (qs[i].l > qs[i].r)
            swap(qs[i].l, qs[i].r);
        if (qs[i].op == 3)
            qs[i].x = (rnd() % (qs[i].r - qs[i].l + 1)) + 1;
        else
            qs[i].x = (rnd() % vmax) + 1;
        if (qs[i].op == 4)
            qs[i].y = (rnd() % vmax) + 1;
    }

    map<int,long long> mp; mp[0] = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] != a[i-1])
            mp[i] = a[i];

    // debug_range(mp);
    for (int i = 0; i < m; i++) {
        // printf("\n");
        // printf("query op:%d, l:%d, r:%d, x:%d, y:%d\n", qs[i].op, qs[i].l, qs[i].r, qs[i].x, qs[i].y);
        
        if (qs[i].op == 1) {
            long long tmp = get_num(mp, qs[i].r + 1);
            mp[qs[i].r + 1] = tmp;
            tmp = qs[i].x + get_num(mp, qs[i].l);
            mp[qs[i].l] = tmp;
            for (auto it = mp.lower_bound(qs[i].l + 1); it != mp.end() && it->first <= qs[i].r; it++)
                it->second += qs[i].x;
        } else if (qs[i].op == 2) {
            long long tmp = get_num(mp, qs[i].r + 1);
            mp[qs[i].r + 1] = tmp;
            vector<int> era;
            for (auto it = mp.lower_bound(qs[i].l); it != mp.end() && it->first <= qs[i].r; it++)
                era.push_back(it->first);
            for (int x : era)
                mp.erase(x);
            mp[qs[i].l] = qs[i].x;
        } else if (qs[i].op == 3) {
            map<long long,int> smp;
            int r = mp.lower_bound(qs[i].l) != mp.end() ? min(qs[i].r + 1, mp.lower_bound(qs[i].l)->first) : qs[i].r + 1;
            smp[get_num(mp, qs[i].l)] = r - qs[i].l;
            for (auto it = mp.lower_bound(qs[i].l); it != mp.end() && it->first <= qs[i].r; it++) {
                auto it2 = it; it2++;
                int r = it2 != mp.end() ? min(it2->first, qs[i].r + 1) : qs[i].r + 1;
                smp[it->second] += r - it->first;
            }
            for (auto it = smp.begin(); it != smp.end(); it++) {
                if (it->second >= qs[i].x) {
                    printf("%lld\n", it->first);
                    break;
                }
                qs[i].x -= it->second;
            }
        } else {
            int r = mp.lower_bound(qs[i].l) != mp.end() ? min(qs[i].r + 1, mp.lower_bound(qs[i].l)->first) : qs[i].r + 1;
            long long sum = (pow(get_num(mp, qs[i].l), qs[i].x, qs[i].y) * ((r - qs[i].l) % qs[i].y)) % qs[i].y;
            for (auto it = mp.lower_bound(qs[i].l); it != mp.end() && it->first <= qs[i].r; it++) {
                auto it2 = it; it2++;
                int r = it2 != mp.end() ? min(it2->first, qs[i].r + 1) : qs[i].r + 1;
                sum = (sum + (pow(it->second,qs[i].x,qs[i].y) * (r - it->first)) % qs[i].y) % qs[i].y;
            }
            printf("%lld\n", sum % qs[i].y);
        }

        // debug_range(mp);
    }

    return 0;
}