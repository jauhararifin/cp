#include <bits/stdc++.h>

using namespace std;

int n,h;
long long k,p[100000],lp;
bool sieve[1000001];

int main() {
	memset(sieve, 0, sizeof(sieve));
	sieve[1] = 1;
	for (int i = 2; i <= 1000000; i++)
		if (!sieve[i])
			for (long long j = (long long)i*(long long)i; j <= 1000000; j += i)
				sieve[j] = 1;
	
	ios::sync_with_stdio(0);
	cin>>n>>k;
	for (int i = 0; i < n; i++) cin>>p[i];
	sort(p, p + n);
	lp = 0;
	h = 0;
	for (int i = 0; i < n && k >= p[i]; i++)
		if (lp == 0 && !sieve[p[i]])
			lp = p[i];
		else if (sieve[p[i]])
			k -= p[i], h++;
	if (lp > 0 && k >= lp)
		h++;
	if (h == n)
		cout<<"One Punch!"<<endl;
	else
		cout<<h<<endl;
	return 0;
}
