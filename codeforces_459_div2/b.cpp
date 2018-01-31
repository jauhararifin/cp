#include <bits/stdc++.h>

using namespace std;

int n,m;
unordered_map<string,string> dns;

int main() {
    ios::sync_with_stdio(0);
    cin>>n>>m;
    while (n--) {
        string x,y; cin>>x>>y;
        dns[y] = x;
    }

    while (m--) {
        string x, y; cin>>x>>y;
        cout<<x<<" "<<y<<" #"<<dns[y.substr(0, y.length() - 1)]<<"\n";
    }

    return 0;
}