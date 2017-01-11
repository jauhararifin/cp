#include <bits/stdc++.h>

using namespace std;

#define ll long long

int n,m;
int a[2000];

void WA() { printf("ganteng\n"); exit(0); }

int main() {
	scanf("%d", &n);
	m = 0;
	for (int i = 0; i < n; i++)
		scanf("%d", a + i), m += a[i];
		
	if (n % 2 == 0) WA();
	if (n > 2) {
		bool urut = 1;
		for (int i = 2; i < n && urut; i++) if ((a[i] < a[i-1]) != (a[1] < a[0])) urut = 0;
		if (urut) WA();
	}
	if (n > 0) {
		int gcd = a[0];
		for (int i = 1; i < n; i++) gcd = __gcd(gcd, a[i]);
		if (999999999 % gcd == 0) WA();
	}
	if (n > 3) {
		int coba = 100000;
		srand(time(0));
		while (coba--) {
			int i = rand() % n;
			int j = rand() % n; while (j == i) j = (j + 1) % n;
			int k = rand() % n; while (k == i || k == j) k = (k + 1) % n;
			if (a[k] < a[j]) swap(j, k); if (a[k] < a[i]) swap(i,k);
			long long x = a[i];
			long long y = a[j];
			long long z = a[k];
			if (x*x + y*y == z*z) WA();
		}
	}
		
	printf("%d\n", m);
	return 0;
}
