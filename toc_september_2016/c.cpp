#include <bits/stdc++.h>

#define ll long long

using namespace std;

int a,b,c,d;

ll f(int a, int b, int range) {
	if (range < 0) return 1 - range > b ? 0 : min(b+range, a);
	if (range > 0) return 1 + range > a ? 0 : min(a-range, b);
	return min(a,b); 
}

int main() {
	scanf("%d%d%d%d", &a, &b, &c, &d);
	
	long long h = 0LL;
	for (int i = -1000000; i <= 1000000; i++) {
		h += 4LL*f(a,b,i)*f(c,d,i);
		h %= 1000000000;
	}
		
	if (h % 4 == 0) printf("%lld\n", h/4);
	else printf("%lld\n", h - h % 4);
	
	return 0;
}
