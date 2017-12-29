#include <bits/stdc++.h>

using namespace std;

string s;

int main() {
    cin>>s;
    int n = 0;
    for (char x : s)
        if (x == 'a' || x == 'i' || x == 'u' || x == 'e' || x == 'o' || x == '1' || x == '3' || x == '5' || x == '7' || x == '9')
            n++;
    cout<<n<<endl;
    return 0;
}