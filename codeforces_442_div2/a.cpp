#include <bits/stdc++.h>

using namespace std;

string str;

int main() {
	ios::sync_with_stdio(0);
	getline(cin, str);
	int count = 0;
	for (string s : {"Danil", "Olya", "Slava", "Ann", "Nikita"}) {
		int i = 0;
		while (i >= 0 && i < str.length()) {
			i = str.find(s, i);
			if (i >= 0) {
				count++;
				i += s.length();
			}
		}
	}
	if (count == 1)
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;
	return 0;
}