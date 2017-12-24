#include <bits/stdc++.h>

using namespace std;

int n,h;
set<char> p;
char a[2], b[100001];

int main() {
	scanf("%d", &n);
	for (char i = 'a'; i <= 'z'; i++) p.insert(i);
	h = 0;
	while (n--) {
		scanf("%s%s", a, b);
		if (a[0] == '!') {
			if (p.size() == 1) h++;
			set<char> newset;
			for (int i = 0; b[i] != 0; i++)
				if (p.find(b[i]) != p.end())
					newset.insert(b[i]);
			p = newset;
		} else if (a[0] == '.') {
			for (int i = 0; b[i] != 0; i++)
				p.erase(b[i]);
		} else if (a[0] == '?') {
			char x = b[0];
			if (p.size() == 1 && *(p.begin()) != x) h++;
			if (p.size() > 1 && n > 0)
				p.erase(x);
		}
		// printf("candidate: "); for (char x : p) printf("%c", x); printf("\n");
	}
	printf("%d\n", h);
	return 0;
}