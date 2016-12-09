#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll memo1[2001][2001];
ll memo2[2001][2001];

const ll mod = 1000000007LL;

ll solve(char * str, int k) {
	memset(memo1, 0, sizeof memo1);
	memset(memo2, 0, sizeof memo2);
	int len = (int) strlen(str);
	memo2[0][0] = str[0] == '0' ? 1 : 2;
	memo2[0][1] = 0;
	for (int i = 0; i < len-1; i++) {
		memo1[i][0] = (i + 2) % mod;
		memo1[i][1] = ((i*(i+1))/2) % mod;
		if (i > 0) memo2[i][0] = str[i] == '0' ? 1 : memo2[i-1][0] + 1;
		if (i > 0) memo2[i][1] = str[i] == '0' ? memo2[i-1][0] - 1 : memo1[i-1][0] + memo2[i-1][1] - 1;
		memo2[i][0] %= mod;
		memo2[i][1] %= mod;
		for (int j = 2; j <= i; j++) {
			memo1[i][j] = memo1[i-1][j-1] + memo1[i-1][j];
			memo2[i][j] = str[i] == '0' ? memo2[i-1][j-1] : memo1[i-1][j-1] + memo2[i-1][j];
			memo1[i][j] %= mod;
			memo2[i][j] %= mod;
		}
	}
	/*
	for (int j = 0; j <= k; j++) {
		for (int i = 0; i < len; i++)
			cout<<memo2[i][j]<<" ";
		cout<<endl;
		for (int i = 0; i < len; i++)
			cout<<memo1[i][j]<<" ";
		cout<<endl<<endl;
	}
	*/
	if (len == 1 && k == 0 && str[0] == '1') return 1;
	else if (len == 1) return 0;
	
	if (len == 2 && k == 0 && str[0] == '1') return 0;
	if (len == 2 && k == 0 && str[0] == '0') return 1;
	if (len == 2 && k == 1 && str[0] == '1' && str[1] == '1') return 1;
	if (len == 2) return 0;
	
	return (memo1[len-2][k] + memo2[len-2][k-1]) % mod;
}

char a[2001],b[2001];
int k;

int main() {	
	scanf("%s%s", a, b);
	scanf("%d", &k);
	
	char* p = a; while (*p == '0') p++; reverse(p, a + strlen(a));
	char* q = b; while (*q == '0') q++; reverse(q, b + strlen(b));
	
	ll h = solve(q,k) - solve(p,k); //cout<<"? "<<h<<endl;
	
	int tmp = 0;
	int last = 0;
	int one = 0;
	while (*p != 0 && *p != '1') p++;
	if (*p == '1') one++;
	for (p++; *p != 0; p++)
		if (*p == '1') one++, last = 0;
		else last++, tmp++;
	tmp -= last; tmp++;
	if (one == 1) tmp = 0;
	//cout<<"tmp "<<tmp<<endl;
	
	h += tmp == k;
	
	cout<<((h % mod) + mod) % mod<<endl;
	
	return 0;
}
