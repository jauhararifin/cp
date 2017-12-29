#include <bits/stdc++.h>

using namespace std;

int n,r;

int main() {
    scanf("%d%d", &n, &r);

    vector<pair<int,double> > pos;
    while (n--) {
        int x; scanf("%d", &x);
        double y = r;
        for (pair<int,double> c : pos)
            if (abs(c.first - x) <= 2*r)
                y = max(y, c.second + sqrt((2*r)*(2*r) - abs(c.first - x)*abs(c.first - x)));
        pos.push_back(make_pair(x,y));
        printf("%.6lf", y); if (n == 0) printf("\n"); else printf(" ");
    }
    return 0;
}