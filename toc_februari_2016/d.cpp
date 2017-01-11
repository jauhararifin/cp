#include <bits/stdc++.h>

using namespace std;

int n,k,t;
int sv[10000001];

int power(int a, int b) {
	if (b == 0) return 1;
	if (b == 1) return a;
	if (b == 2) return a*a;
	int c = power(a, b/2);
	if (b % 2 == 0)
		return c*c;
	else
		return c*c*a;
}

int main() {
	ios::sync_with_stdio(0);
	memset(sv, 0, sizeof sv);
	sv[1] = 1;
	for (long long i = 2; i <= 10000000; i++)
		if (!sv[i]) {
			sv[i] = i;
			for (long long j = i*i; j <= 10000000; j += i)
				sv[j] = i;
		}
	
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &k);
		if (k >= 24 || n == 1)
			printf("Tidak\n");
		else {
			while (n > 1) {
				k--;
				n /= sv[n];
			}
				
			if (k == 0)
				printf("Ya\n");
			else
				printf("Tidak\n");
		}
	}
	return 0;
}
