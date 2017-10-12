#include <bits/stdc++.h>

using namespace std;

template<typename T>
class polynomial {
public:
	vector<T> arr;
	bool modEnable = false;
	T mod;

	void useMod(T m) {
		mod = m;
		modEnable = true;
	}

	T& operator[](const uint i) {
		if (i >= arr.size())
			arr.resize(i + 1, T());
		return arr[i];
	};
	uint degree() {
		return arr.size() - 1;
	};

	template<typename S>
	friend ostream& operator<<(ostream& os, polynomial<S> a);

	template<typename S>
	friend polynomial<S> operator+(const polynomial<S>& a, const polynomial<S>& b);

	template<typename S>
	friend polynomial<S> operator-(polynomial<S> a);

	template<typename S>
	friend polynomial<S> operator-(polynomial<S>& a, polynomial<S>& b);
};

template<typename T>
ostream& operator<<(ostream& os, polynomial<T> a) {
	os<<a.arr[0];
	for (int i = 1; i < (int) a.arr.size(); i++)
		os<<" "<<a.arr[i];
	return os;
};

template<typename S>
polynomial<S> operator+(const polynomial<S>& a, const polynomial<S>& b) {
	polynomial<S> res;
	for (int i = 0; i < a.arr.size() || i < b.arr.size(); i++)
		if (!a.modEnable)
			res[i] = (i < a.arr.size() ? a.arr[i] : S()) + (i < b.arr.size() ? b.arr[i] : S());
		else
			res[i] = (((i < a.arr.size() ? a.arr[i] : S()) % a.mod) + ((i < b.arr.size() ? b.arr[i] : S()) % a.mod)) % a.mod;
	return res;
};

template<typename S>
polynomial<S> operator-(polynomial<S> a) {
	for (int i = 0; i < (int) a.arr.size(); i++) {
		a.arr[i] *= -1;
		if (a.modEnable)
			a.arr[i] = ((a.arr[i] % a.mod) + a.mod) % a.mod;
	}
	return a;
};

template<typename S>
polynomial<S> operator-(polynomial<S>& a, polynomial<S>& b) {
	return a + (-b);
};

int main() {
	polynomial<int> p;
	p[5] = 5;
	p[3] = 2;
	polynomial<int> q;
	q[1] = 2;
	q[3] = 5;
	q[7] = 9;
	cout<<p<<endl<<q<<endl<<(p+q)<<endl<<(-q)<<endl<<(p-q)<<endl;
	return 0;
}