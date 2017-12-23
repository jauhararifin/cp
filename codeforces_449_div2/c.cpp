#include <bits/stdc++.h>

#define ull unsigned long long

using namespace std;

const string s = "What are you doing at the end of the world? Are you busy? Will you save us?";
const string t = "What are you doing while sending \"\"? Are you busy? Will you send \"\"?";

long long q,n,k;

ull power_of_two(int n) {
    if (n > 63)
        return -1;
    return 1LL<<(ull)n;
}

ull count_len(ull n) {
    if (n == 0) return s.length();
    ull t = power_of_two(n-1);
    if (t == (ull) -1)
        return -1;
    if (286*t - 68 < t)
        return -1;
    else
        return 286*t - 68;
}

char solve(long long n, long long k) {
    if (n == 0) {
        if (k >= s.length()) return '.';
        return s[k];
    }
    if (k < 34) return t[k];
    k -= 34;
    ull len_before = count_len(n-1);
    if (k < len_before)
        return solve(n-1, k);
    k -= len_before;
    if (k < 32)
        return t[34 + k];
    k -= 32;
    if (k < len_before)
        return solve(n-1, k);
    k -= len_before;
    if (k < 2)
        return t[66 + k];
    return '.';
}

int main() {
    ios::sync_with_stdio(0);
    cin>>q;
    while (q--) {
        cin>>n>>k; k--;
        cout<<solve(n,k);
    }
    cout<<endl;
    return 0;
}