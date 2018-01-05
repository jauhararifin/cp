#include <bits/stdc++.h>

using namespace std;

long long a,b,x,y,z;

int main() {
	scanf("%lld%lld%lld%lld%lld", &a, &b, &x, &y, &z);
	printf("%lld\n", max(0LL, (2LL*x+y)-a) + max(0LL, (y+3LL*z)-b));
	return 0;
}