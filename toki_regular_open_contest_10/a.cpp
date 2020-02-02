#include <bits/stdc++.h>

using namespace std;

long long a,b,c,d,e,f;

int main() {
	scanf("%lld%lld%lld%lld%lld%lld", &a, &b, &c, &d, &e, &f);
	long long h = (c * (c-1))/2 + (c-1)*(d-1) - (f*(f-1))/2 + b*(c+d-1);
	printf("%lld\n", h);
	return 0;
}
