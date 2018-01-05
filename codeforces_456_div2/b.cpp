#include <bits/stdc++.h>

using namespace std;

long long n,k;

int main() {
	scanf("%lld%lld", &n, &k);
	
	long long x = 0LL;
	for (int i = 0; i < 64; i++)
		if ((n>>(long long)i) & 1)
			x = 1LL<<(long long) i;
	
	if (k > 1)
		printf("%lld\n", (x-1) | x);
	else
		printf("%lld\n", n);

	return 0;
}