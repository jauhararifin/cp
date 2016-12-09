#include <bits/stdc++.h>

using namespace std;

int n,telur,daging;
string last,ne;

int main() {
	ios::sync_with_stdio(0);
	cin>>n;
	telur = daging = 0;
	last = "SERI";
	for (int i = 1; i <= n; i++) {
		cout<<i<<" ";
		if (last == "SAITAMA")
			cout<<"GENOS"<<endl;
		else
			cout<<"SAITAMA"<<endl;
		fflush(stdout);
		
		cin>>ne;
		if (ne == "SAITAMA" && last == "SERI") daging++;
		if (ne == "SERI" && last == "SERI") telur++;
		if (ne == "GENOS" && last == "SERI") telur++;
		if (ne == "SAITAMA" && last == "SAITAMA") daging++;
		if (ne == "SERI" && last == "SAITAMA") telur++;
		if (ne == "GENOS" && last == "GENOS") telur++;
		if (ne == "SERI" && last == "GENOS") daging++;
		//printf(">>> %d %d\n", daging, telur);
		
		last = ne;
	}
	cout<<daging<<" "<<telur<<endl;
	fflush(stdout);
	return 0;
}
