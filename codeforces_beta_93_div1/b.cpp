#include <bits/stdc++.h>

using namespace std;

vector<int> z_algorithm(string s) {
	int l = 0, r = 0;
	int n = (int) s.length();
	vector<int> result;
	result.push_back(n);
	for (int i = 1; i < n; i++) {
	 	if (i > r) {
	    	l = r = i;
	    	while (r < n && s[r - l] == s[r])
	    		r++;
	    	result.push_back(r - l);
	    	r--;
	  	} else {
	    	int k = i - l;
	    	if (result[k] < r - i + 1)
	    		result.push_back(result[k]);
	    	else {
	      		l = i;
	      		while (r < n && s[r - l] == s[r])
	      			r++;
	      		result.push_back(r-l);
	      		r--;
	    	}
	  	}
	}
	return result;
}

int main() {
	ios::sync_with_stdio(0);
	string s;
	getline(cin, s);
	int ns = (int) s.length();
	int n = 0;
	int p = -1;
	vector<int> z = z_algorithm(s);

	int b = 0;
	for (int i = 1; i < (int) ns; i++) {
		if (z[i] + i == ns && z[i] <= b && z[i] > n) {
			n = min(b, z[i]);
			p = i;
		}
		b = max(b, z[i]);
	}
	if (p < 0)
		cout<<"Just a legend"<<endl;
	else
		cout<<s.substr(p, n)<<endl;
	return 0;
}
