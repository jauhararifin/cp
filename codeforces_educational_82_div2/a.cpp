#include <bits/stdc++.h>

using namespace std;

int t,n;
char s[1000];

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%s", s);
		n = (int) strlen(s);
		int i = 0, j = n - 1;
		for (; i < n && s[i] == '0'; i++);
		for (; j >= 0 && s[j] == '0'; j--);
		int h = 0;
		for (; i <= j; i++) if (s[i] == '0') h++;
		printf("%d\n", h);
	}
	return 0;
}
