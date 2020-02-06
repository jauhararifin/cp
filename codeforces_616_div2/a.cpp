#include <bits/stdc++.h>

using namespace std;

int t,n;
char s[3001];

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		scanf("%s", s);

		string ans = "";
		for (int i = 0; i < n; i++)
			if ((s[i]-'0') % 2 == 1)
				ans += s[i];
		if (ans.length() >= 2)
			printf("%c%c\n", ans[0], ans[1]);
		else
			printf("-1\n");
	}
	return 0;
}
