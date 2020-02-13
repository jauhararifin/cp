#include <bits/stdc++.h>

using namespace std;

int t,bb[26];
char s[201],p[10000];

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%s", s);
		int ns = (int) strlen(s);
		memset(p, 0, sizeof p);
		memset(bb, 0, sizeof bb);
		
		int no = 0;
		int pos = 500;
		int lo = 500;
		int hi = 500;
		p[pos] = s[0];
		bb[s[0]-'a'] = 1;
		for (int i = 1; i < ns; i++) {
			if (p[pos-1] == s[i]) pos--;
			else if (p[pos+1] == s[i]) pos++;
			else if (p[pos-1] == 0 && !bb[s[i]-'a']) {
				pos--;
				lo--;
				p[pos] = s[i];
			} else if (p[pos+1] == 0 && !bb[s[i]-'a']) {
				pos++;
				hi++;
				p[pos] = s[i];
			} else {
				no = 1;
				break;
			}
			bb[s[i]-'a'] = 1;
		}

		if (no) {
			printf("NO\n");
		} else {
			printf("YES\n");
			memset(bb, 0, sizeof bb);
			for (int i = lo; i <= hi; i++) {
				printf("%c", p[i]);
				bb[p[i]-'a'] = 1;
			}
			for (int i = 0; i < 26; i++)
				if (!bb[i])
					printf("%c", i + 'a');
			printf("\n");
		}
	}
	return 0;
}
