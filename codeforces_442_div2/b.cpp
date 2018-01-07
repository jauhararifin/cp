#include <bits/stdc++.h>

using namespace std;

string s;
int ns, mf[5001], mg[5001], mh[5001];

int h(int x) {
	if (mh[x] > -1) return mh[x];
	if (x >= ns) return 0;
	return mh[x] = (s[x] == 'a' ? 1 + h(x+1) : h(x+1));
}

int g(int x) {
	if (mg[x] > -1) return mg[x];
	if (x >= ns) return 0;
	return mg[x] = (s[x] == 'a' ? max(h(x), g(x+1)) : 1 + g(x+1));	
}

int f(int x) {
	if (mf[x] > -1) return mf[x];
	if (x >= ns) return 0;
	return mf[x] = (s[x] == 'a' ? 1 + f(x+1) : max(g(x), f(x+1)));
}

int main() {
	ios::sync_with_stdio(0);
	cin>>s; ns = (int) s.length();
	memset(mf, -1, sizeof mf);
	memset(mg, -1, sizeof mg);
	memset(mh, -1, sizeof mh);
	cout<<f(0)<<endl;
	return 0;
}