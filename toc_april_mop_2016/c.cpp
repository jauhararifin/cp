#include <bits/stdc++.h>

#define ll long long
#define ull unsigned long long

using namespace std;

const ull mag = 32452867ULL;
const ull inv = 17004125811683213739ULL;

int n;
ll h;
string s;
ull a[500001],b[500001];

bool check_n(string s) {
	if (s.length() > 11) return 0;
	if (s.length() > 0) {
		if (s[0] != '-' && (s[0] < '0' || s[0] > '9')) return 0;
		if (s[0] == '-' && s.length() == 1) return 0;
		if (s[0] == '-' && s[1] == '0') return 0;
		if (s[0] == '0' && s.length() > 1) return 0;
		for (int i = 1; i < (int) s.length(); i++)
			if (s[i] < '0' || s[i] > '9') return 0;
	}
	return 1;
}

ull pangkat(ull a, ull b) {
	if (b == 0) return 1;
	if (b == 1) return a;
	ull x = pangkat(a, b/2);
	if (b % 2) return x * x * a;
	else return x * x;
}

int main() {
	cin>>n;
	if (n == 1) {
		cin>>s;
		sscanf(s.c_str(), "%lld", &h);
		if (check_n(s) && h >= -2147483648LL && h <= 2147483646LL)
			cout<<"AC"<<endl;
		else
			cout<<"WA"<<endl;
	} else {
		cin>>s;
		if (s.length() % 2 != 0) { cout<<"WA"<<endl; return 0; }
		memset(a, 0, sizeof a); memset(b, 0, sizeof b);
		ull all_hash = 0; for (int i = 0; i < (int) s.length()/2; i++) {
			a[i+1] = all_hash = all_hash * mag + (ull) s[i];
			b[i+1] = b[i] * mag + (ull) s[i+s.length()/2];
		}
		bool success = 0;
		for (int i = 1; !success && i < (int) s.length()/2; i++)
			if (a[i] * pangkat(mag,s.length()/2-i) + b[s.length()/2-i] == all_hash)
				success = 1;
		if (success) cout<<"AC"<<endl;
		else cout<<"WA"<<endl;
	}
	return 0;
}
