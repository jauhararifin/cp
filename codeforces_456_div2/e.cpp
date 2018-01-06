#include <bits/stdc++.h>

using namespace std;

const long long MAX = 1000000000000000000LL;

int n,p[16];
long long k;

void generate_set(vector<long long> &s, int initial) {
    s.push_back(1LL);
    for (int i = initial; i < n; i += 2) {
        vector<long long> tmp = {1LL};
        while (MAX / tmp[tmp.size()-1] >= (long long) p[i])
            tmp.push_back(tmp[tmp.size()-1] * (long long) p[i]);
        
        vector<long long> ntmp;
        for (long long x : s)
            for (long long y : tmp) {
                if (1LL < y && MAX / x >= y && x*y > 1LL)
                    ntmp.push_back(x*y);
            }
        for (long long x : ntmp)
            s.push_back(x);
    }
    sort(s.begin(), s.end());
}

long long find_k(vector<long long> &sa, vector<long long> &sb, long long num) {
    long long res = 0LL;
    for (long long x : (sa.size() < sb.size() ? sa : sb)) {
        vector<long long> &tm = sa.size() < sb.size() ? sb : sa;
        res += (long long) (upper_bound(tm.begin(), tm.end(), num/x) - tm.begin());
    }
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", p + i);
    scanf("%lld", &k);
    
    sort(p, p + n);
    vector<long long> va, vb;
    generate_set(va, 0);
    generate_set(vb, 1);

    long long lo = 1LL, hi = MAX, h = -1;
    while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        if (find_k(va, vb, mid) >= k)
            h = mid, hi = mid - 1;
        else
            lo = mid + 1;
    }
    cout<<h<<endl;

    return 0;
}