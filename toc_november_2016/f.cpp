#include <bits/stdc++.h>

typedef unsigned long long ull;
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;

const ull magic = 353531ll;
const ull imagic = 13375403936601409075ull;

char p[200001];
int lp,h;
ull thash[200001];

ull pangkat(ull base, ull exp) {
	if (exp == 0) return 1;
	ull t = pangkat(base, exp/2);
	return t * t * (ull)(exp % 2 ? base : 1ll);
}
ull count_hash(int begin, int end) {
	return (ull)(thash[begin] - (end < lp ? thash[end] : 0)) * pangkat(imagic, lp-end);
}
bool is_prefix(pii first, pii second) {
	int len = min(first.se - first.fi, second.se - second.fi);
	return count_hash(first.fi, first.fi + len) == count_hash(second.fi, second.fi + len);
}

int main() {
	ios::sync_with_stdio(0);
	cin>>p; lp = (int) strlen(p);
	ull tmp = 1;
	for (int i = lp-1; i >= 0; i--)
		thash[i] = (i < lp-1 ? thash[i+1] : 0) + (ull)p[i] * (ull)tmp, tmp *= magic;
	
	pii longest = pii(0,1);
	stack<pii> st; st.push(pii(0,1));
	for (int i = 1; i < lp; i++) {
		pii top = st.top();
		if (p[i] == p[0])
			st.push(pii(i,i+1));
		else if ((top.se - top.fi + 1) > (longest.se - longest.fi)) {
			longest.fi = top.fi;
			longest.se = top.se + 1;
			st.pop();
			st.push(longest);
		} else {
			while (!is_prefix(pii(top.fi, i + 1),pii(longest.fi, longest.se))) {
				st.pop();
				top = st.top();
			}
			top = st.top();
			top.se = i + 1;
			if (i + 1 - top.fi > longest.se - longest.fi)
				longest = pii(top.fi, i + 1);
			st.pop();
			st.push(top);
		}
	}
	
	vector<int> h;
	while (!st.empty())
		h.push_back(st.top().fi), st.pop();
	sort(h.begin(), h.end());
	cout<<h.size()<<endl;
	for (int i = 0; i < (int) h.size()-1; i++)
		cout<<h[i]+1<<" ";
	cout<<h[h.size()-1]+1<<endl;
	return 0;
}
