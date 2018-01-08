#include <bits/stdc++.h>

using namespace std;

int n,t;
pair<pair<int,int>,int> prob[200000];

int main() {
    scanf("%d%d", &n, &t);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &prob[i].first.second, &prob[i].first.first), prob[i].second = i;
    sort(prob, prob + n);
    
    int lo = 0, hi = n, ans = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;

        int rmtime = t;
        int count = 0;
        for (int i = 0; i < n && prob[i].first.first <= rmtime && count < mid; i++)
            if (prob[i].first.second >= mid) {
                count++;
                rmtime -= prob[i].first.first;
            }
        if (count >= mid) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    vector<int> p;
    int count = 0;
    for (int i = 0; i < n && prob[i].first.first <= t && count < ans; i++)
        if (prob[i].first.second >= ans) {
            count++;
            t -= prob[i].first.first;
            p.push_back(prob[i].second);
        }
    printf("%d\n%d\n", count, p.size());
    for (int i = 0; i < p.size(); i++) {
        printf("%d", p[i] + 1);
        if (i < p.size() - 1)
            printf(" ");
    }
    printf("\n");
}