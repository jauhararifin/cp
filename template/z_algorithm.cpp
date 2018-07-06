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
	return 0;
}
