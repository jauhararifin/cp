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

    map<int,int> mp; mp[0] = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] != a[i-1])
            mp[i] = a[i];

    for (int i = 0; i < m; i++) {
        auto it = mp.lower_bound(qs[i].l);
        
        if (qs[i].op == 1) {
            if (mp.find(qs[i].l) == mp.end()) {
                auto it = mp.lower_bound(qs[i].l);
                it--;
                mp[qs[i].l] = it->second + qs[i].x;
            }

            int last = -1;
            for (auto it = mp.lower_bound(qs[i].l); it != mp.end() && it->first <= qs[i].r; it++) {
                last = it->second;
                it->second += qs[i].x;
            }
            if (qs[i].r < n - 1)
                mp[qs[i].r+1] = last + qs[i].x;
        } else if (qs[i].op == 2) {
            auto it = mp.lower_bound(qs[i].l);
            if (qs[i].l > 0) {
                it--;
                
            }
        }
    }

    return 0;
}