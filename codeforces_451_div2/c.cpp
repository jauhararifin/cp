#include <bits/stdc++.h>

using namespace std;

int n;
map<string, set<string> > phones;

bool is_suffix(string a, string b) {
    if (b.length() > a.length()) return 0;
    return equal(a.end() - b.length(), a.end(), b.begin());
}

int main() {
    ios::sync_with_stdio(0);
    cin>>n;
    while (n--) {
        string s; cin>>s;
        int m; cin>>m;
        set<string>& vec = phones[s];
        while (m--) {
            string x; cin>>x;
            bool inserted = 0;
            for (string tmp : vec)
                if (is_suffix(tmp, x)) {
                    inserted = 1;
                    break;
                } else if (is_suffix(x, tmp)) {
                    inserted = 1;
                    vec.erase(tmp);
                    vec.insert(x);
                    break;
                }
            if (!inserted)
                vec.insert(x);
        }
    }

    cout<<phones.size()<<endl;
    for (auto i = phones.begin(); i != phones.end(); i++) {
        cout<<i->first<<" "<<i->second.size();
        for (string x : i->second)
            cout<<" "<<x;
        cout<<endl;
    }

    return 0;
}