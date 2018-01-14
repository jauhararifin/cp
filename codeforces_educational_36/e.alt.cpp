#include <bits/stdc++.h>

using namespace std;

int n,q;

inline int get_num(map<int,int>& m, int pos) {
    auto it = m.lower_bound(pos);
    if (it != m.end() && it->first == pos)
        return it->second;
    it--;
    return it->second;
}

int main() {
    scanf("%d%d", &n, &q);

    map<int,int> intervals;
    intervals[1] = 1;
    int h = n;
    while (q--) {
        int l,r,k; scanf("%d%d%d", &l, &r, &k);
        
        int tmp = get_num(intervals, r + 1);
        intervals[r + 1] = tmp;
        tmp = get_num(intervals, l);
        intervals[l] = tmp;

        // for (auto i = intervals.begin(); i != intervals.end(); i++)
        //     printf("(%d,%d) ", i->first, i->second);
        // printf("\n");

        vector<pair<int,int> > deleting;
        int zero = 0, one = 0;
        for (auto i = intervals.lower_bound(l); i != intervals.upper_bound(r); i++)
            deleting.push_back(make_pair(i->first, i->second));
        deleting.push_back(make_pair(r + 1,0));
        for (int i = 0; i < deleting.size(); i++) {
            if (i > 0) {
                if (deleting[i-1].second)
                    one += deleting[i].first - deleting[i-1].first;
                else
                    zero += deleting[i].first - deleting[i-1].first;
            }
            if (i < deleting.size() - 1)
                intervals.erase(deleting[i].first);
        }

        // printf("one:%d, zero:%d\n", one, zero);
        // for (auto i = intervals.begin(); i != intervals.end(); i++)
        //     printf("(%d,%d) ", i->first, i->second);
        // printf("\n");

        if (k == 1)
            intervals[l] = 0, h -= one;
        else
            intervals[l] = 1, h += zero;
        printf("%d\n", h);
    }

    return 0;
}