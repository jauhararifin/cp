#include <bits/stdc++.h>

using namespace std;

int n;
char p[1001];
string ans;
queue<int> que;

void decide(int x, int y, int z) {
	if (ans == "SCS") p[x] = 'J', p[z] = 'J';
	else if (ans == "SCC") p[x] = 'J', p[z] = 'R';
	else if (ans == "CSS") p[x] = 'R', p[y] = 'J', p[z] = 'J';
	else if (ans == "CSC") p[x] = 'R', p[y] = 'J', p[z] = 'R';
	else if (ans == "CCS") p[x] = 'R', p[y] = 'R', p[z] = 'J';
	else if (ans == "CCC") p[x] = 'R', p[y] = 'R', p[z] = 'R';
	else if (ans == "SSC") p[x] = 'J', p[y] = 'J';
	else p[x] = p[y] = p[z] = 'J';
	if (p[x] == 0) que.push(x);
	if (p[y] == 0) que.push(y);
	if (p[z] == 0) que.push(z);
}
void decide(int x, int y) {
	if (ans == "SC") p[x] = 'J';
	else if (ans == "CS") p[x] = 'R', p[y] = 'J';
	else if (ans == "CC") p[x] = 'R', p[y] = 'R';
	else p[x] = p[y] = 'J';
	if (p[x] == 0) que.push(x);
	if (p[y] == 0) que.push(y);
}

int main() {
	ios::sync_with_stdio(0);
	cin>>n;
	for (int i = 1; i <= n; i++) que.push(i), p[i] = 0;
	if (n == 2) {
		que.pop(), que.pop();
		cout<<2<<endl<<1<<" "<<2<<endl; fflush(stdout); cin>>ans;
		decide(1, 2);
		if (!que.empty())
			cout<<2<<endl<<2<<" "<<1<<endl, fflush(stdout), cin>>ans, decide(2, 1);
	} else
		while (!que.empty())
			if (que.size() > 2) {
				int x = que.front(); que.pop();
				int y = que.front(); que.pop();
				int z = que.front(); que.pop();
				cout<<3<<endl<<x<<" "<<y<<" "<<z<<endl; fflush(stdout); cin>>ans;
				decide(x, y, z);
			} else if (que.size() == 2) {
				int x = que.front(); que.pop();
				int y = que.front(); que.pop();
				cout<<2<<endl<<x<<" "<<y<<" "<<endl; fflush(stdout); cin>>ans;
				decide(x, y);
			} else {
				cout<<2<<endl<<que.front()<<" "<<(que.front() == 1 ? 2 : 1)<<endl; fflush(stdout); cin>>ans;
				p[que.front()] = ans[0] == 'S' ? 'J' : 'R';
				que.pop();
			}
	cout<<-1<<endl;
	for (int i = 1; i <= n; i++) cout<<p[i]; cout<<endl; fflush(stdout);
	return 0;
}
