#include <bits/stdc++.h>

using namespace std;

const double pi = acos(-1);
double xa,ya,xb,yb,xo,yo,r;

int main() {
    scanf("%lf%lf%lf%lf%lf%lf%lf", &xa, &ya, &xb, &yb, &xo, &yo, &r);
    bool a_inside = hypot(xa-xo,ya-yo) <= r;
    bool b_inside = hypot(xb-xo,yb-yo) <= r;
    if (a_inside || b_inside) {
        printf("%.12lf\n", hypot(xa-xb,ya-yb));
    } else {
        double dist = -1;
        double ang = -1;
        for (double x = 0; x < 2*acos(-1); x += 0.00005) {
            double xx = r*cos(x)+xo;
            double yy = r*sin(x)+yo;
            double d = hypot(xa-xx,ya-yy)+hypot(xb-xx,yb-yy);
            if (dist < 0 || d < dist) {
                dist = d;
                ang = x;
            }
        }

        double lo = ang - 0.00005;
        double hi = ang + 0.00005;
        for (int i = 0; i < 1000; i++) {
            double pl = lo + (hi - lo) / 3;
            double pr = lo + (hi - lo) * 2.0 / 3.0;

            double xl = r*cos(pl)+xo;
            double yl = r*sin(pl)+yo;
            double dl = hypot(xa-xl,ya-yl)+hypot(xb-xl,yb-yl);

            double xr = r*cos(pr)+xo;
            double yr = r*sin(pr)+yo;
            double dr = hypot(xa-xr,ya-yr)+hypot(xb-xr,yb-yr);

            if (dl < dr)
                hi = (lo + hi) / 2;
            else
                lo = (lo + hi) / 2;
        }

        double mid = (lo + hi) / 2.0;
        double xl = r*cos(mid)+xo;
        double yl = r*sin(mid)+yo;
        dist = hypot(xa-xl,ya-yl)+hypot(xb-xl,yb-yl);

        printf("%.12lf\n", dist);
    }
    return 0;
}