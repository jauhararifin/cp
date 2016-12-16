#include <bits/stdc++.h>

using namespace std;

int n,k,s;

int main() {
	scanf("%d%d%d", &n, &k, &s);
	if (k >= n) k = n;
	if (s == 0)
		n = k*((n+k-1)/k);
	printf("%d\n", n);
	bool b = 0;
	while (n >= k) {
		for (int i = 0; i < k; i++) {
			if (k % 2) {
				if ((k*b+i) % (2*k) < k) printf("%c", (k*b+i) % 2 ? '-':'+');
				else printf("%c", (k*b+i) % 2 ? '+':'-');
			} else {
				if ((k*b+i) % (2*k) <= k) printf("%c", (k*b+i) % 2 ? '-':'+');
				else printf("%c", (k*b+i) % 2 ? '+':'-');
			}
			printf(" %d\n", b ? (i == 0 ? k : i) : k-i);
		}
		n -= k;
		b = !b;
	}
	if (n > 0) {
		if (s > 0) {
			if (!b) for (int i = 0; i < n; i++) printf("%c %d\n", i%2?'-':'+',n-i);
			else if (n <= k/2+1) {
				printf("+ %d\n", k/2+1);
				for (int i = n-1; i >= 1; i--)
					printf("%c %d\n", (i-n+1)%2 ? '-' : '+', i);
			} else {
				printf("+ %d\n", n/2+k/2+1);
				for (int i = 1; i <= n-1; i++)
					printf("%c %d\n", i % 2 ? '-' : '+',i);
			}
		}
	}
	
	return 0;
}
