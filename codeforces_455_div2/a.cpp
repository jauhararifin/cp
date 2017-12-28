#include <bits/stdc++.h>

using namespace std;

string a,b;

int main() {
    cin>>a>>b;
    cout<<a[0];
    for (int i = 1; i < a.length(); i++) {
        if (a[i] >= b[0])
            break;
        cout<<a[i];
    }
    cout<<b[0]<<endl;
    return 0;
}