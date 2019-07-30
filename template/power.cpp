#include <bits/stdc++.h>

using namespace std;

template<typename T>
T power(T base, long long exp, T identity) {
    T tmp = base;
    T ans = identity;
    while (exp) {
        if (exp & 1)
            ans *= tmp;
        tmp *= tmp;
        exp >>= 1;
    }
    return ans;
}

int main() {
    cout<<power(5,7,1)<<endl;
    cout<<power(5,0,1)<<endl;
    cout<<power(5,1,1)<<endl;
    cout<<power(5,2,1)<<endl;
    cout<<power(5,3,1)<<endl;
    cout<<power(5,4,1)<<endl;
    return 0;
}