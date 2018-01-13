#include <bits/stdc++.h>

using namespace std;

string a,b;

bool solve(int pos) {
    if (pos >= a.length()) return 1;

    bool found = 0;
    for (int i = pos; i < a.length() && !found; i++)
        if (a[i] == b[pos]) {
            found = 1;
            swap(a[i], a[pos]);
        }
    if (found && solve(pos + 1))
        return 1;

    int m = -1;
    for (int i = pos; i < a.length(); i++)
        if (a[i] < b[pos] && (m < 0 || a[i] > a[m]))
            m = i;
    if (m < 0) return 0;
    swap(a[pos], a[m]);
    sort(a.begin() + pos + 1, a.end());
    reverse(a.begin() + pos + 1, a.end());
    return 1;
}

int main() {
    ios::sync_with_stdio(0);
    cin>>a>>b;

    sort(a.begin(), a.end());
    if (a.length() < b.length()) {
        reverse(a.begin(), a.end());
        cout<<a<<endl;
        return 0;
    }
    solve(0);
    cout<<a<<endl;

    return 0;
}