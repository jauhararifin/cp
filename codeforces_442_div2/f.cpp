#include <bits/stdc++.h>

using namespace std;

int n,k,q,x,co[200001],cnt[200001],used[200001];
long long a[100000],p[100000],ans[100000];
pair<pair<int,int>,int> que[100000];

bool cmp(pair<pair<int,int>,int> a, pair<pair<int,int>,int> b) {
    int sq = (int) sqrt(n);
    if ((a.first.first / sq) == (b.first.first / sq))
        return a.first.second < b.first.second;
    return a.first.first < b.first.first;
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &x), a[i] = x == 1 ? 1 : -1;
    for (int i = 0; i < n; i++)
        scanf("%d", &x), a[i] *= x;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        que[i].second = i;
        scanf("%d%d", &que[i].first.first, &que[i].first.second);
        que[i].first.first--;
        que[i].first.second--;
    }
    sort(que, que + q, cmp);

    p[0] = a[0];
    for (int i = 1; i < n; i++)
        p[i] = p[i-1] + a[i];
    int c = 0;
    unordered_map<long long,int> compress; compress[0] = c++;
    for (int i = 0; i < n; i++) {
        if (compress.find(p[i]) == compress.end())
            compress[p[i]] = c++;
        if (compress.find(p[i]-k) == compress.end())
            compress[p[i]-k] = c++;
        co[compress[p[i]]] = compress[p[i] - k];
        p[i] = compress[p[i]];
    }

    // printf("A:"); for (int i = 0; i < n; i++)
    //     printf(" %3lld", a[i]); printf("\n");
    // printf("P:"); for (int i = 0; i < n; i++)
    //     printf(" %3lld", p[i]); printf("\n");

    int lo = 0, hi = 0;
    cnt[0] = 1;
    used[co[p[0]]] = 1;
    long long last_ans = cnt[co[p[0]]];
    for (int i = 0; i < q; i++) {
        int left = que[i].first.first, right = que[i].first.second, iq = que[i].second;
        // printf("query %d: %d %d\n", iq, left, right);
        ans[iq] = last_ans;
        while (hi < right) {
            hi++;
            cnt[hi > 0 ? p[hi-1] : 0]++;
            used[co[p[hi]]]++;
            ans[iq] += cnt[co[p[hi]]];
            // printf("hi++, ans+%d\n", cnt[p[hi] - k]);
        }
        while (lo > left) {
            lo--;
            cnt[lo > 0 ? p[lo-1] : 0]++;
            used[co[p[lo]]]++;
            ans[iq] += used[lo > 0 ? p[lo-1] : 0];
            // printf("lo--, ans+%d\n", used[lo > 0 ? p[lo-1] : 0]);
        }
        while (lo < left) {
            ans[iq] -= used[lo > 0 ? p[lo-1] : 0];
            used[co[p[lo]]]--;
            cnt[lo > 0 ? p[lo-1] : 0]--;
            lo++;
            // printf("lo++\n");
        }
        while (hi > right) {
            ans[iq] -= cnt[co[p[hi]]];
            used[co[p[hi]]]--;
            cnt[hi > 0 ? p[hi-1] : 0]--;
            hi--;
            // printf("hi--\n");
        }
        last_ans = ans[iq];
    }

    for (int i = 0; i < q; i++)
        printf("%lld\n", ans[i]);

    return 0;
}