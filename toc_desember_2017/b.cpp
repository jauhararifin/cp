#include <bits/stdc++.h>

using namespace std;

int q,n;
pair<double,double> p[6];

int main() {
    scanf("%d", &q);
    while (q--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%lf%lf", &p[i].first, &p[i].second);
            p[i].first *= sqrt(3);
        }
        if (n == 1) {
            printf("BISA\n");
        } else if (n == 2) {
            if (hypot(p[0].first - p[1].first, p[0].second - p[1].second) > 1e-6)
                printf("BISA\n");
            else
                printf("TIDAK\n");    
        } else if (n > 2) {
            int pos[6] = {0,1,2,3,4,5};
            bool can = 0;
            do {
                double h = hypot(p[0].first - p[1].first, p[0].second - p[1].second);
                double d;
                switch (abs(pos[0] - pos[1])) {
                    case 1: case 5: d = h; break;
                    case 2: case 4: d = h/sqrt(3.0); break;
                    case 3: d = h/2.0; break;
                }
                if (d == 0)
                    continue;

                bool right = 1;
                for (int i = 0; i < n && right; i++)
                    for (int j = 0; j < i && right; j++) {
                        double dist_should;
                        switch (abs(pos[i] - pos[j])) {
                            case 1: case 5: dist_should = d; break;
                            case 2: case 4: dist_should = d*sqrt(3.0); break;
                            case 3: dist_should = d*2.0; break;
                        }

                        double dist_real = hypot(p[i].first - p[j].first, p[i].second - p[j].second);
                        if (fabs(dist_should - dist_real) > 1e-6)
                            right = 0;
                    }
                if (right) can = 1;
            } while (!can && next_permutation(pos + 1, pos + 6));

            if (can)
                printf("BISA\n");
            else
                printf("TIDAK\n");
        }
    }
    return 0;
}