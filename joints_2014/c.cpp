#include <bits/stdc++.h>

using namespace std;

long long n,k,x,h,p[1000001];

int main(void) {
	memset(p, 0, sizeof p);
	
	scanf("%lld%lld", &n, &k);
	while (n--) {
		scanf("%lld", &x);
		p[x%k]++;
	}
	
	h = 0LL;
	for (int i = 0; i < k; i++)
		h += (p[i]*(p[i]-1))/2LL;
		
	printf("%lld\n", h);
	
	return 0;
}
