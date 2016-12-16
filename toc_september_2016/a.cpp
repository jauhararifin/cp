#include <bits/stdc++.h>

using namespace std;

int n,k,m,a[1000],h;
char s[1001];

int main() {
	scanf("%d%d%d", &n, &k, &m);
	scanf("%s", s);
	for (int i = 0; i < n; i++)
		scanf("%d", a + i), a[i] = s[i] == '0' ? 0 : a[i];
		
	sort(a, a + n);
	h = 0;
	for (int i = n-1; i >= 0; i--)
		if (k > 0) k--;
		else if (m > 0) {
			m--;
			h += a[i]/2;
		} else h += a[i];
		
	printf("%d\n", h);
		
	return 0;
}
