#include <bits/stdc++.h>

using namespace std;

int n,k,p[1000],q;

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++)
		scanf("%d", &p[i]);
	sort(p, p+n);
	q = 2000000000;
	for (int i = 0; i < n-k+1; i++)
		q = min(q, p[i+k-1] - p[i]);
	printf("%d\n", q);
}
