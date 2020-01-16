#include <bits/stdc++.h>

using namespace std;

int t,a,b;

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &a, &b);

		int x = 9;
		int c = 0;
		while (x <= b) {
			c++;
			x = x*10 + 9;
		}
		printf("%lld\n", (long long) a * (long long) c);
	}
	return 0;
}
