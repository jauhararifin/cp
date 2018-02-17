#include <bits/stdc++.h>

using namespace std;

long long n;
int k;

int main() {
	scanf("%lld%d", &n, &k);
	long long rem = 1000000000000000000LL;
	long long sz = 0;
	int tbox = -1;
	for (int i = 0; i < k; i++) {
		long long a; scanf("%lld", &a);
		if (n % a < rem || (n % a == rem && a > sz)) {
			sz = a;
			tbox = i;
			rem = n % a;
		}
	}
	printf("%d %lld\n", tbox + 1, n / sz);
	return 0;
}