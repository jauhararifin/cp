#include <bits/stdc++.h>

using namespace std;

string a, b;

int main() {
    cin>>a>>b;
    if (a.find(b) != string::npos) {
        cout<<"TIDAK"<<endl;
        return 0;
    }

    string z = a + (char) ((b[0] - 'a' + rand()) % 26 + 'a');
    cout<<"YA"<<endl;
    cout<<z<<endl;

    return 0;
}