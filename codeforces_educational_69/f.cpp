#include <bits/stdc++.h>

using namespace std;

namespace jauhar_template {
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
        out << c.num;
        return out;
    }

    template<typename T, long long mod>
    istream& operator>>(istream &in, automod<T,mod> &c) {
        in >> c.num;
        c.num = ((c.num % mod) + mod) % mod;
        return in;
    }

    template<typename T>
    class square_matrix {
    public:
        square_matrix() {
            n = 1;
            arr = new T[1];
        }

        square_matrix(int size):n(size) {
            arr = new T[n*n];
        }
        
        square_matrix(const square_matrix<T>& m) {
            n = m.n;
            arr = new T[n*n];
            for (int i = 0; i < n*n; i++)
                arr[i] = m.arr[i];
        }

        square_matrix(square_matrix<T>&& m) {
            n = m.n;
            arr = m.arr;
            m.arr = 0;
            m.n = 0;
        }

        ~square_matrix() {
            if (arr) delete [] arr;
        }

        square_matrix<T>& resize(int size) {
            delete [] arr;
            n = size;
            arr = new T[n*n];
        }

        square_matrix<T>& operator=(square_matrix<T> a) {
            swap(arr, a.arr);
            swap(n, a.n);
            return *this;
        }

        T* operator[](int i) { return arr + i * n; }

        bool operator==(const square_matrix<T>& a) const {
            if (this == &a) return 1;
            if (n != a.n) return 0;
            for (int i = 0; i < n*n; i++)
                if (arr[i] != a.arr[i]) return 0;
            return 1;
        }

        square_matrix<T> operator+(const square_matrix<T>& a) const {
            assert(n == a.n);
            square_matrix<T> res(n);
            for (int i = 0; i < n*n; i++)
                res.arr[i] = arr[i] + a.arr[i];
            return res;
        }

        square_matrix<T>& operator+=(const square_matrix<T>& a) {
            assert(n == a.n);
            for (int i = 0; i < n*n; i++)
                arr[i] += a.arr[i];
            return (*this);
        }

        square_matrix<T> operator-(const square_matrix<T>& a) const {
            square_matrix<T> res(n);
            for (int i = 0; i < n*n; i++)
                res.arr[i] = arr[i] - a.arr[i];
            return res;
        }

        square_matrix<T>& operator-=(const square_matrix<T>& a) {
            assert(n == a.n);
            for (int i = 0; i < n*n; i++)
                arr[i] -= a.arr[i];
            return (*this);
        }

        square_matrix<T> operator*(const square_matrix<T>& a) const {
            if (n <= 512) return naive_mul(a);
            
            int s = n;
            while (__builtin_popcount(s) != 1) s += s & -s;
            double strassen_ratio = pow(7.0, log2((double) s/ (double) n));
            double naive_ratio = pow(11.0, log2((double) n / 512.0));
            if (strassen_ratio < naive_ratio) return strassen_mul(a);
            return naive_mul(a);
        }

        square_matrix<T> operator*(const T& scalar) const {
            square_matrix<T> res(n);
            for (int i = 0; i < n*n; i++) res.arr[i] = arr[i] * scalar;
            return res;
        }

        vector<T> operator*(const vector<T>& v) const {
            assert(n == (int) v.size());
            vector<T> res(n);
            for (int i = 0; i < n; i++) {
                res[i] = arr[i*n] * v[0];
                for (int j = 1; j < n; j++)
                    res[i] += arr[i*n+j] * v[j];
            }
            return res;
        }

        square_matrix<T>& operator*=(const square_matrix<T>& a) {
            assert(n == a.n);
            square_matrix<T> result = (*this) * a;
            (*this) = result;
            return *this;
        }

        square_matrix<T>& operator*=(const T& scalar) {
            for (int i = 0; i < n*n; i++) arr[i] *= scalar;
        }

        square_matrix<T> operator/(const T& scalar) const {
            square_matrix<T> res(n);
            for (int i = 0; i < n*n; i++) res.arr[i] = arr[i] / scalar;
            return res;
        }

        square_matrix<T>& operator/=(const T& scalar) {
            for (int i = 0; i < n*n; i++) arr[i] /= scalar;
        }

        template<typename U>
        friend ostream& operator<<(ostream& os, const square_matrix<U>& m);

        template<typename U>
        friend istream& operator>>(istream& is, square_matrix<U>& m);

    private:

        square_matrix<T> naive_mul(const square_matrix<T>& m) const {
            assert(n == m.n);
            square_matrix<T> res(n);
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) {
                    res[i][j] = 0;
                    for (int k = 0; k < n; k++)
                        res[i][j] += this->arr[i*n+k] * m.arr[k*n+j];
                }
            return res;
        }

        square_matrix<T> strassen_mul(const square_matrix<T>& m) const {
            assert(n == m.n);
            if (n <= 512) return naive_mul(m);
            
            int s = n;
            while (__builtin_popcount(s) != 1)
                s += s & -s;

            square_matrix<T> a11(s/2), a12(s/2), a21(s/2), a22(s/2);
            square_matrix<T> b11(s/2), b12(s/2), b21(s/2), b22(s/2);
            for (int i = 0; i < s; i++)
                for (int j = 0; j < s; j++) {
                    T va = i >= n || j >= n ? 0 : arr[i*n+j];
                    T vb = i >= n || j >= n ? 0 : m.arr[i*n+j];
                    if (i < s/2 && j < s/2) { a11[i][j] = va; b11[i][j] = vb; }
                    else if (i < s/2) { a12[i][j-s/2] = va; b12[i][j-s/2] = vb; }
                    else if (j < s/2) { a21[i-s/2][j] = va; b21[i-s/2][j] = vb; }
                    else { a22[i-s/2][j-s/2] = va; b22[i-s/2][j-s/2] = vb; }
                }
            
            auto m1 = (a11 + a22).strassen_mul(b11 + b22);
            auto m2 = (a21 + a22).strassen_mul(b11);
            auto m3 = a11.strassen_mul(b12 - b22);
            auto m4 = a22.strassen_mul(b21 - b11);
            auto m5 = (a11 + a12).strassen_mul(b22);
            auto m6 = (a21 - a11).strassen_mul(b11 + b12);
            auto m7 = (a12 - a22).strassen_mul(b21 + b22);

            auto c11 = m1 + m4 - m5 + m7;
            auto c12 = m3 + m5;
            auto c21 = m2 + m4;
            auto c22 = m1 - m2 + m3 + m6;

            square_matrix<T> c(n);
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (i < s/2 && j < s/2) c[i][j] = c11[i][j];
                    else if (i < s/2) c[i][j] = c12[i][j-s/2];
                    else if (j < s/2) c[i][j] = c21[i-s/2][j];
                    else c[i][j] = c22[i-s/2][j-s/2];
            
            return c;
        }

        T* arr;
        int n;
    };

    template<typename U>
    square_matrix<U> operator*(const U& scalar, const square_matrix<U>& m) {
        return m * scalar;
    }

    template<typename U>
    ostream& operator<<(ostream& os, const square_matrix<U>& m) {
        for (int i = 0; i < m.n; i++) {
            os<<m.arr[i*m.n];
            for (int j = 1; j < m.n; j++)
                os<<" "<<m.arr[i*m.n+j];
            os<<endl;
        }
        return os;
    }

    template<typename U>
    istream& operator>>(const istream& is, square_matrix<U>& m) {
        for (int i = 0; i < m.n * m.n; i++) is>>m.arr[i];
        return is;
    }

    template<typename T>
    square_matrix<T> identity(int n) {
        square_matrix<T> res(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                res[i][j] = i == j ? 1 : 0;
        return res;
    }

    template<typename T>
    square_matrix<T> zeros(int n) {
        square_matrix<T> res(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                res[i][j] = 0;
        return res;
    }
}
using namespace jauhar_template;
const int mod = 998244353;
typedef automod<int,mod> intmod;

int n,a[1000],m,f[3][3];
intmod comb[1000][4];
square_matrix<intmod> mat[4],memo[32];
vector<pair<int,int> > b[1000];

inline int grundy(int a, int b, int c) {
    if (a != 0 && b != 0 && c != 0) return 0;
    if (a != 1 && b != 1 && c != 1) return 1;
    if (a != 2 && b != 2 && c != 2) return 2;
    return 3;
}

int main() {
    ios::sync_with_stdio(0);
    
    cin>>n;
    for (int i = 0; i < n; i++) cin>>a[i];
    cin>>m;
    for (int i = 0; i < m; i++) {
        int x,y,c; cin>>x>>y>>c;
        b[x-1].push_back({y,c-1});
    }
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin>>f[i][j];

    for (int i = 0; i < 4; i++) mat[i] = zeros<intmod>(64);
    for (int i = 0; i < 64; i++)
        for (int j = 0; j < 64; j++)
            for (int c = 0; c < 3; c++) {
                int prev_grundies[3];
                memset(prev_grundies, -1, sizeof prev_grundies);
                for (int k = 0; k < 3; k++)
                    if (f[c][k])
                        prev_grundies[k] = ((j>>(k<<1))&3);
                if (grundy(prev_grundies[0], prev_grundies[1], prev_grundies[2]) == (i & 3) && (i >> 2 == (j & 15)))
                    mat[c][i][j] = 1;
            }
    mat[3] = mat[0] + mat[1] + mat[2];

    memo[0] = mat[3];
    for (int i = 1; i < 32; i++)
        memo[i] = memo[i-1] * memo[i-1];

    vector<intmod> v(64);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 64; j++) v[j] = 0;
        v[0b111111] = 1;

        int last = 0;
        sort(b[i].begin(), b[i].end());
        if (b[i].empty() || b[i].back().first < a[i])
            b[i].push_back({a[i],3});

        for (auto x : b[i]) {
            if (last < x.first - 1) {
                int power = x.first - 1 - last;
                for (int j = 0, bit = 1; bit <= power; bit <<= 1, j++)
                    if (power & bit) v = memo[j] * v;
            }
            v = mat[x.second] * v;
            last = x.first;
        }
        for (int j = 0; j < 4*4*4; j++) comb[i][j & 3] += v[j];
    }

    intmod curr[4]; memset(curr, 0, sizeof curr); curr[0] = 1;
    intmod next_curr[4];
    for (int i = 0; i < n; i++) {
        memset(next_curr, 0, sizeof next_curr);
        auto x = comb[i];
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                next_curr[i^j] += curr[i] * x[j];
        for (int i = 0; i < 4; i++) curr[i] = next_curr[i];
    }
    cout<<curr[0]<<endl;
    
    return 0;
}