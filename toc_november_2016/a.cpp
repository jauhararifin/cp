#include <bits/stdc++.h>

using namespace std;

int n;
char p[10];

int toint(char* x) {
	if (x[0] == 'A') return 1;
	if (x[0] == 'J') return 11;
	if (x[0] == 'Q') return 12;
	if (x[0] == 'K') return 13;
	if (x[0] == '1' && x[2] != 0) return 10;
	return (int) x[0]-'0';
}
const char* tochar(int x) {
	if (x == 1) return "A";
	if (x == 11) return "J";
	if (x == 12) return "Q";
	if (x == 13) return "K";
	if (x == 10) return "10";
	char *p = (char*) malloc(2);
	p[0] = x + '0';
	p[1] = 0;
	return p;
}

int main() {
	scanf("%d", &n);
	while (n--) {
		scanf("%s", p);
		char x = p[strlen(p)-1];
		int i = toint(p) + 1;
		bool first = 1;
		while (i <= 13) {
			if (!first) printf(" ");
			printf("%s%c", tochar(i), x);
			first = 0;
			i++;
		}
		i = toint(p) - 1;
		while (i > 0) {
			if (!first) printf(" ");
			printf("%s%c", tochar(i), x);
			i--;
			first = 0;
		}
		printf("\n");
	}
	return 0;
}
