#include <bits/stdc++.h>
#define point pair<double,pair<double, double> >
#define fi first
#define se second
using namespace std;

int n;
double r,p[100000];

int main() {
  scanf("%d%lf", &n, &r);
  for (int i = 0; i < n; i++) {
    double x,y,z;
    scanf("%lf%lf%lf", &x, &y, &z);
    p[i] = sqrt(x*x + y*y + z*z);
  }
  sort(p, p + n);

  // printf("p: "); for (int i = 0; i < n; i++) printf("%.2lf ", p[i]); printf("\n");

  double h = p[0];
  for (int i = 1; i < n; i++) {
    if (p[i] > h + r) h += p[i] - h;
    else h += r;
  }
  printf("%.10lf\n", h);

  return 0;
}