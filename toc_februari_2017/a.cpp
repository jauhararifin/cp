#include <bits/stdc++.h>

using namespace std;

int ns;
string str;

int main() {
	ios::sync_with_stdio(0);
	cin>>ns>>str;

	bool can = 0; for (char c : str) if (c == '1' || c == '0') can = 1;
	if (!can) {
		cout<<-1<<endl;
		return 0;
	}
	
	int h = 0; for (char c : str) if (c > '1') h++;

	int pos = 0;
	for (char c : str)
		if (c == '0')
			pos++;
		else if (c == '1')
			break;
	h += min(ns - h - 1, pos);

	cout<<h<<endl;
	return 0;
}