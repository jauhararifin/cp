#include <bits/stdc++.h>

using namespace std;

int main() {
    int n = 2500;
    int k = 2;

    cout<<k<<" "<<n<<endl;
    string s;
    for (int i = 0; i < n; i++)
        s += (char) (rand() % 26 + 'a');
    for (int i = 0; i < k; i++) {
        string t = s;
        // swap(t[rand() % t.length()], t[rand() % t.length()]);
        t[rand() % t.length()] = (char) (rand() % 26 + 'a');
        cout<<t<<endl;
    }

    return 0;
}