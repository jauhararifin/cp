#include <bits/stdc++.h>

using namespace std;

double p,q,r,s,t,u;

inline double f(double x) {
    return p*exp(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x*x + u;
}

int main() {
    while (scanf("%lf%lf%lf%lf%lf%lf", &p, &q, &r, &s, &t, &u) != EOF) {
        double lo = 0.0, hi = 1.0;
        if (f(lo) < 0 || f(hi) > 0) printf("No solution\n");
        else {
            if (lo > hi) swap(lo, hi);
            double h = (lo + hi) / 2.0;
            for (int i = 0; i < 200; i++) {
                h = (lo + hi) / 2.0;
                if (f(h) < 0) hi = h;
                else lo = h;
            }
            printf("%.4lf\n", h);
        }
    }
    return 0;
}