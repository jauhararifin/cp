#include <bits/stdc++.h>

using namespace std;

int n,l,r;
char s[100001];

int main() {
	scanf("%d", &n);
	scanf("%s", s);
	l = r = 0;
	for (int i = 0; i < n; i++)
		if (s[i] == 'L') l++;
		else r++;
	printf("%d\n", 1 + l + r);
	return 0;
}
