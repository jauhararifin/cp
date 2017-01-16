#include <bits/stdc++.h>

using namespace std;

int l,h,n,x,y,z,t;

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		l = h = 0;
		while (n--) {
			scanf("%d%d%d", &x, &y, &z);
			l += min(x,min(y,z));
			h += max(x,max(y,z));
		}
		printf("%d %d\n", l, h);
	}
	return 0;
}
