#include <bits/stdc++.h>

using namespace std;

template<typename T, long long mod>
class automod {
public:
    automod():num(0){}
    automod(T x):num(x % mod){}
    
    inline automod<T,mod> operator+(automod<T,mod> const& a) {
        return {(0LL+a.num+num) % mod};
    }

    inline automod<T,mod> operator-(automod<T,mod> const& a) {
        return {(((0LL+num-a.num) % mod) + mod) % mod};
    }

    inline automod<T,mod> operator*( automod<T,mod> const& a) {
        return {(1LL*a.num*num) % mod};
    }

    inline automod<T,mod>& operator=( automod<T,mod> const& a) {
        num = a.num % mod;
        return *this;
    }

    inline automod<T,mod>& operator*=( automod<T,mod> const& a) {
        num = (1LL*a.num*num) % mod;
        return *this;
    }

    inline automod<T,mod>& operator+=( automod<T,mod> const& a) {
        num = (0LL+a.num+num) % mod;
        return *this;
    }

    inline automod<T,mod>& operator-=( automod<T,mod> const& a) {
        num = (((0LL+num-a.num) % mod) + mod) % mod;
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
    out << c.num;
    return out;
}

template<typename T, long long mod>
istream& operator>>(istream &in, automod<T,mod> &c) {
    in >> c.num;
    c.num = ((c.num % mod) + mod) % mod;
    return in;
}

const long long mod = 1e9+7;

int n,v[200000],m[200000];
automod<long long, mod> s[200000];
pair<int,int> p[200000];
unordered_map<int,vector<pair<int, automod<long long, mod> > > > mp;

bool cmp(pair<int,int> a, pair<int,int> b) { return a.second < b.second; }

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &p[i].second, &p[i].first);
    
    sort(p, p + n, cmp);
    for (int i = 0; i < n; i++) {
        int lo = 0;
        int hi = i - 1;
        int j = -1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (p[mid].second <= p[i].first) {
                lo = mid + 1;
                j = mid;
            } else
                hi = mid - 1;
        }
        
        if (j > -1) {
            v[i] = m[j] + p[i].second - p[i].first;

            int lo = 0;
            int hi = mp[m[j]].size() - 1;
            int k = -1;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (mp[m[j]][mid].first <= j) {
                    k = mid;
                    lo = mid + 1;
                } else
                    hi = mid - 1;
            }
            if (k > -1)
                s[i] = mp[m[j]][k].second;
            else
                s[i] = 1LL;

            if (mp[v[i]].size() == 0)
                mp[v[i]].push_back({i,s[i]});
            else
                mp[v[i]].push_back({i, mp[v[i]].back().second + s[i]});
        } else {
            v[i] = p[i].second - p[i].first;
            s[i] = 1LL;
            if (mp[v[i]].size() == 0)
                mp[v[i]].push_back({i,1LL});
            else
                mp[v[i]].push_back({i, mp[v[i]].back().second + 1LL});
        }

        m[i] = max(i > 0 ? m[i-1] : 0, v[i]);
    }

    int h = p[n-1].second - v[n-1];
    int lo = p[n-1].first;
    automod<long long, mod> res = 0;
    for (int i = n-1; i >= 0; i--) {
        if (p[i].second <= lo)
            break;
        if (h > p[i].second - v[i]) {
            h = p[i].second - v[i];
            res = s[i];
        } else if (h == p[i].second - v[i])
            res = res + s[i];
        lo = max(lo, p[i].first);
    }
    cout<<res<<endl;

    return 0;
}