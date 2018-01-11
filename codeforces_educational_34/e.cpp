#include <bits/stdc++.h>

using namespace std;

int n,k;
string s[5000];
unordered_set<int> vs[5000];

int main() {
	ios::sync_with_stdio(0);
	cin>>k>>n;
	for (int i = 0; i < k; i++)
		cin>>s[i];

	if (k == 1) {
		swap(s[0][0], s[0][1]);
		cout<<s[0]<<endl;
		return 0;
	}

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < n; j++)
			if (s[i][j] != s[0][j])
				vs[i].insert(j);
		if (vs[i].size() > 4) {
			cout<<-1<<endl;
			return 0;
		}
	}
	vs[1].insert(0); // at least swap once

	bool contain_pair = 0;
	bool used[26];
	memset(used, 0, sizeof used);
	for (int i = 0; i < n; i++)
		if (!used[s[0][i]-'a'])
			used[s[0][i]-'a'] = 1;
		else {
			contain_pair = 1;
			vs[1].insert(i);
			break;
		}

	for (int i = 0; i < n; i++)
		for (int j : vs[1])
			if (i != j) {
				string& tests = s[0]; swap(tests[i], tests[j]);

				bool success = 1;
				for (int ii = 1; ii < k && success; ii++) {
					unordered_set<int> test = vs[ii]; test.insert(i); test.insert(j);
					vector<int> diff;
					for (int jj : test)
						if (tests[jj] != s[ii][jj])
							diff.push_back(jj);
					if (diff.size() == 0 && !contain_pair)
						success = 0;
					if (diff.size() == 1)
						success = 0;
					if (diff.size() == 2 && (tests[diff[0]] != s[ii][diff[1]] || tests[diff[1]] != s[ii][diff[0]]))
						success = 0;
					if (diff.size() > 2)
						success = 0;
				}
				
				if (success) {
					cout<<tests<<endl;
					return 0;
				}
				swap(tests[i], tests[j]);
			}
	cout<<-1<<endl;

	return 0;
}