#include <bits/stdc++.h>

#define pii pair<int,int>
#define fi first
#define se second
#define ll long long

using namespace std;

int t,n;
pair<string,pii> p[50000],q[50000];

bool cmp1(pair<string,pii> a, pair<string,pii> b) { return a.se.fi > b.se.fi; }
bool cmp2(pair<string,pii> a, pair<string,pii> b) { return a.se.se > b.se.se; }

int main() {
	ios::sync_with_stdio(0);
	
	cin>>t;
	while (t--) {
		cin>>n;
		for (int i = 0; i < n; i++)
			cin>>p[i].fi>>p[i].se.fi>>p[i].se.se,q[i] = p[i];
		
		sort(p, p + n, cmp1);
		sort(q, q + n, cmp2);
		
		string hkandidat[6];
		long long h = -1;
		int x[3];
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 6; j++)
				for (int k = 0; k < 6; k++)
					if (i != j && j != k && i != k) {
						long long hc = (ll)p[i].se.fi * (ll)p[j].se.fi * (ll)p[k].se.fi;
						long long hg = 1;
						for (int l = 0, c = 0; l < 6 && c < 3; l++)
							if (q[l].fi != p[i].fi && q[l].fi != p[j].fi && q[l].fi != p[k].fi)
								hg *= q[l].se.se, x[c++] = l;
						if (hc + hg > h) {
							h = hc + hg;
							hkandidat[0] = p[i].fi; hkandidat[1] = p[j].fi; hkandidat[2] = p[k].fi;
							hkandidat[3] = q[x[0]].fi; hkandidat[4] = q[x[1]].fi; hkandidat[5] = q[x[2]].fi;
						}
					}
		
		cout<<h<<endl;
		cout<<hkandidat[0]<<" "<<hkandidat[1]<<" "<<hkandidat[2]<<endl;
		cout<<hkandidat[3]<<" "<<hkandidat[4]<<" "<<hkandidat[5]<<endl;
	}
	return 0;
}
