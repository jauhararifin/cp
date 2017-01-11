#include <bits/stdc++.h>

using namespace std;

const
	double eps = 1e-5;

struct point {
	double x,y;
};
point make_point(double _x, double _y) { point p; p.x = _x; p.y = _y; return p; }
struct line {
	int a,b,c;
};

int n;
point p,q,r,test;
line ld[100];

double dist(point a, point b) {
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
bool in_line(line l, point p) {
	return fabs(l.a*p.x + l.b*p.y + l.c) <= eps;
}
point intersect(line a, line b) {
	point p;
	p.x = (double) (a.b*b.c - a.c*b.b)/(double) (a.a*b.b - a.b*b.a);
	p.y = (double) (a.a*b.c - a.c*b.a)/(double) (a.b*b.a - a.a*b.b);
	return p;
}
double area(point a, point b, point c) {
	return fabs((a.x*b.y) + (b.x*c.y) + (c.x*a.y) - (a.y*b.x) - (b.y*c.x) - (c.y*a.x))/2.0;
}

int main(void) {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d%d%d", &ld[i].a, &ld[i].b, &ld[i].c);		
	scanf("%lf%lf", &test.x, &test.y);
	
	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++)
			for (int k = j+1; k < n; k++) {
				if (in_line(ld[i], test) || in_line(ld[j], test) || in_line(ld[k], test))
					continue;
				
				p = intersect(ld[i], ld[j]);
				q = intersect(ld[i], ld[k]);
				r = intersect(ld[j], ld[k]);
				
				if (dist(p,q) <= eps || dist(p,r) <= eps || dist(q,r) <= eps)
					continue;
				
				if (fabs(area(p,q,r) - (area(test,p,q) + area(test,p,r) + area(test,q,r))) <= eps) {
					printf("YA\n");
					return 0;
				}
			}
	printf("TIDAK\n");	
	return 0;
}
