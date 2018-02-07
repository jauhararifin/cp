#include <bits/stdc++.h>

using namespace std;

int n;
string s[50];
vector<int> ans;

int main() {
    ios::sync_with_stdio(0);
    cin>>n;
    cin.ignore();
    for (int i = 0; i < n; i++)
        getline(cin, s[i]);
    for (int i = 0; i < n; i++) {
        bool can = 0;
        for (int j = 0; j < n && !can; j++)
            for (int k = 0; k < n && !can; k++)
                if (i != j && i != k && k != j && s[j] + s[k] == s[i])
                    can = 1;
        if (can)
            ans.push_back(i+1);
    }
    if (ans.size() > 0)
        cout<<ans[0];
    for (int i = 1; i < ans.size(); i++)
        cout<<" "<<ans[i];
    cout<<endl;
    return 0;
}