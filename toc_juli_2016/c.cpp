#include <bits/stdc++.h>

#define pii pair<int,int>
#define fi first
#define se second

using namespace std;

char s[301],t[301];
int n;
pii memo[300][300];

int main() {
	scanf("%s%s", s, t);
	n = (int) strlen(s);
	
	memset(memo, 0, sizeof memo);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			int a = i > 0 ? memo[i-1][j].fi : 0;
			int b = j > 0 ? memo[i][j-1].fi : 0;
			int c = 1 + (i > 0 && j > 0 ? memo[i-1][j-1].fi : 0);
			if (a > b)
				memo[i][j].fi = a, memo[i][j].se = 1;
			else
				memo[i][j].fi = b, memo[i][j].se = 2;
			if (s[i] == t[j] && c > a && c > b)
				memo[i][j].fi = c, memo[i][j].se = 3;
		}
		
	vector<int> a,b;
	string lcs = "";
	for (int i = n-1, j = n-1; i >= 0 && j >= 0;)
		switch (memo[i][j].se) {
			case 1: i--; break;
			case 2: j--; break;
			case 3: lcs += s[i]; a.push_back(i--); b.push_back(j--); break;
		}
	reverse(lcs.begin(), lcs.end());
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	
	int m = n - lcs.length();
	for (int i = 0; i < (int) a.size(); i++) {
		for (int j = i > 0 ? a[i-1]+1 : 0; j < a[i] && m > 0; j++)
			printf("%c", s[j]), m--;
		for (int j = i > 0 ? b[i-1]+1 : 0; j < b[i] && m > 0; j++)
			printf("%c", t[j]), m--;
		printf("%c", s[a[i]]);
	}
	for (int j = a.size() > 0 ? a[a.size()-1]+1 : 0; j < n && m > 0; j++)
		printf("%c", s[j]), m--;
	for (int j = b.size() > 0 ? b[b.size()-1]+1 : 0; j < n && m > 0; j++)
		printf("%c", t[j]), m--;
	printf("\n");
	
	return 0;
}
