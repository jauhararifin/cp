#include <bits/stdc++.h>

using namespace std;

// when you are too lazy to write mod operation...

template<typename T, long long mod>
class automod {
public:
    automod():num(0){}
    automod(T x):num(x % mod){}
    automod(automod<T,mod>& m):num(m.num){}
    
    inline automod<T,mod>& operator=(const automod<T,mod>& a) {
        num = a.num % mod;
        return *this;
    }

    inline bool operator==(const automod<T,mod>& a) const {
        return num == a.num;
    }
    
    inline automod<T,mod> operator+(const automod<T,mod>& a) const {
        return {(0LL+a.num+num) % mod};
    }

    inline automod<T,mod>& operator+=(const automod<T,mod>& a) {
        num = (0LL+a.num+num) % mod;
        return *this;
    }

    inline automod<T,mod> operator-(const automod<T,mod>& a) const {
        return {(((0LL+num-a.num) % mod) + mod) % mod};
    }
    
    inline automod<T,mod>& operator-=(const automod<T,mod>& a) {
        num = (((0LL+num-a.num) % mod) + mod) % mod;
        return *this;
    }

    inline automod<T,mod> operator*(const automod<T,mod>& a) {
        return {(1LL*a.num*num) % mod};
    }

    inline automod<T,mod>& operator*=(const automod<T,mod>& a) {
        num = (1LL*a.num*num) % mod;
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

int main() {
    automod<int, 29> n(31);
    n *= 27;
    n += 10;
    n -= 7;
    cout<<n<<endl;
    return 0;
}