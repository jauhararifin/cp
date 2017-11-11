#include <bits/stdc++.h>

using namespace std;

int n, h, i, c, m, k;

int main() {
	scanf("%d", &n);
	h = -1;
	c = 0;
	i = 0;
	while (n--) {
		scanf("%d%d", &m, &k);
		i++;
		h = max(h, i);
		c -= k;
		if (c == 0)
			i = 0;
		c += m;
	}
	h = max(h, i);
	printf("%d\n", h*10);
	return 0;
}

