#include <bits/stdc++.h>

using namespace std;

int t,n,x;
char s[100001];

int sign(int x) {
	if (x == 0) return 0;
	return x > 0 ? 1 : -1;
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &x);
		scanf("%s", s);
		
		int sum = 0;
		for (int i = 0; i < n; i++)
			sum += s[i] == '0' ? 1 : -1;

		int ans = x == 0 ? 1 : 0;
		int y = 0;
		for (int i = 0; i < n; i++) {
			y += s[i] == '0' ? 1 : -1;
			int xminy = x-y;
			if (xminy == 0 && sum == 0) {
				ans = -1;
				break;
			} else if (xminy == 0) ans++;
			else if (sum != 0 && xminy % sum == 0 && sign(xminy) == sign(sum)) ans++;
		}
		// nk = x - y
		printf("%d\n", ans);
	}
	return 0;
}
