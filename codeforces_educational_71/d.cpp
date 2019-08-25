#include <bits/stdc++.h>
 
using namespace std;
 
template<typename T, long long mod>
class automod {
public:
    automod():num(0) {}
    automod(T x) {
        if (x > mod) num = x % mod;
        else if (x < -mod) num = (x % mod) + mod;
        else num = x;
    }
    automod(const automod<T,mod>& m):num(m.num) {}
    
    automod<T,mod>& operator=(const automod<T,mod>& a) {
        num = a.num;
        return *this;
    }
 
    automod<T,mod>& operator=(const T& x) {
        num = x;
        if (num > mod) num %= mod;
        else if (num < -mod) num = (num % mod) + mod;
        return *this;
    }
 
    bool operator==(const automod<T,mod>& a) const {
        return num == a.num;
    }
 
    bool operator==(const T& a) const {
        return num == a;
    }
 
    bool operator!=(const automod<T,mod>& a) const {
        return num != a.num;
    }
 
    bool operator!=(const T& a) const {
        return num != a;
    }
 
    bool operator<(const automod<T,mod>& a) const {
        return num < a.num;
    }
 
    bool operator<(const T& a) const {
        return num < a;
    }
 
    bool operator>(const automod<T,mod>& a) const {
        return num < a.num;
    }
 
    bool operator>(const T& a) const {
        return num < a;
    }
    
    automod<T,mod> operator+(const automod<T,mod>& a) const {
        long long x = 0LL+num+a.num;
        if (x > mod) x %= mod;
        return {x};
    }
 
    automod<T,mod>& operator+=(const automod<T,mod>& a) {
        long long temp = 0LL+num+a.num;
        if (temp > mod) temp %= mod;
        num = temp;
        return *this;
    }
 
    automod<T,mod> operator-(const automod<T,mod>& a) const {
        long long temp = 0LL+num-a.num;
        if (temp < -mod) temp = (temp % mod) + mod;
        return {temp};
    }
    
    automod<T,mod>& operator-=(const automod<T,mod>& a) {
        long long temp = 0LL+num-a.num;
        if (temp < -mod) temp = (temp % mod) + mod;
        num = temp;
        return *this;
    }
 
    automod<T,mod> operator*(const automod<T,mod>& a) {
        long long temp = 1LL*num*a.num;
        if (temp > mod) temp %= mod;
        return {temp};
    }
 
    automod<T,mod>& operator*=(const automod<T,mod>& a) {
        long long temp = 1LL*num*a.num;
        if (temp > mod) temp %= mod;
        num = temp;
        return *this;
    }
 
    template<typename U, long long m>
    friend ostream &operator << (ostream &out, const automod<U,m> &c);
 
    template<typename U, long long m>
    friend istream &operator >> (istream &in,  automod<U,m> &c);
private:
    T num;
};
 
template<typename T, long long mod>
ostream& operator<<(ostream &out, const automod<T,mod> &c) {
    out << (((c.num % mod) + mod) % mod);
    return out;
}
 
template<typename T, long long mod>
istream& operator>>(istream &in, automod<T,mod> &c) {
    in >> c.num;
    c.num = ((c.num % mod) + mod) % mod;
    return in;
}
 
int n,a[300000],b[300000];
automod<int,998244353> h,perm[300001];
 
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d%d", a + i, b + i);
 
    perm[0] = 1;
    for (int i = 1; i <= n; i++)
        perm[i] = perm[i-1] * i;
    h = perm[n];
    
    // both a and b increasing
    vector<pair<int,int> > vv;
    for (int i = 0; i < n; i++) vv.push_back({a[i],b[i]});
    sort(vv.begin(), vv.end());
    bool sorted = 1;
    for (int i = 1; i < n && sorted; i++)
        if (vv[i].second < vv[i-1].second)
            sorted = 0;
    if (sorted) {
        map<pair<int,int>,int> mp;
        for (auto x : vv) mp[x]++;
        automod<int,998244353> tmp = 1;
        for (auto x : mp) tmp *= perm[x.second];
        h += tmp; 
        // cout<<"both: "<<tmp<<endl;
    }
 
    // a increasing
    unordered_map<int,int> mp;
    for (int i = 0; i < n; i++) mp[a[i]]++;
    automod<int,998244353> tmp = 1;
    for (auto x : mp) tmp *= perm[x.second];
    h -= tmp;
    // cout<<"a: "<<tmp<<endl;
 
    // b increasing
    mp.clear();
    for (int i = 0; i < n; i++) mp[b[i]]++;
    tmp = 1;
    for (auto x : mp) tmp *= perm[x.second];
    h -= tmp;
    // cout<<"b: "<<tmp<<endl;
 
    cout<<h<<endl;
 
    return 0;
}
