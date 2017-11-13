#include <bits/stdc++.h>

using namespace std;

template <typename A, typename B, typename C>
struct triplet {
	A first;
	B second;
	C third;
	triplet(){}
	triplet(A x) : first(x) {}
	triplet(A x, B y) : first(x), second(y) {}
	triplet(A x, B y, C z) : first(x), second(y), third(z) {}
};

template <typename A, typename B, typename C>
triplet<A,B,C> make_triplet(A a, B b, C c) {
	return triplet<A,B,C>(a,b,c);
}

template <typename A, typename B, typename C>
bool operator==(triplet<A,B,C> a, triplet<A,B,C> b) {
	return a.first == b.first && a.second == b.second && a.third == b.third;
}

template <typename A, typename B, typename C>
bool operator!=(triplet<A,B,C> a, triplet<A,B,C> b) {
	return !(a == b);
}

template <typename A, typename B, typename C>
bool operator<(triplet<A,B,C> a, triplet<A,B,C> b) {
	if (a.first == b.first) {
		if (a.second == b.second)
			return a.third < b.third;
		else
			return a.second < b.second;
	} else
		return a.first < b.first;
}

template <typename A, typename B, typename C>
bool operator<=(triplet<A,B,C> a, triplet<A,B,C> b) {
	if (a.first == b.first) {
		if (a.second == b.second)
			return a.third <= b.third;
		else
			return a.second <= b.second;
	} else
		return a.first <= b.first;
}

template <typename A, typename B, typename C>
bool operator>(triplet<A,B,C> a, triplet<A,B,C> b) {
	if (a.first == b.first) {
		if (a.second == b.second)
			return a.third > b.third;
		else
			return a.second > b.second;
	} else
		return a.first > b.first;
}

template <typename A, typename B, typename C>
bool operator>=(triplet<A,B,C> a, triplet<A,B,C> b) {
	if (a.first == b.first) {
		if (a.second == b.second)
			return a.third >= b.third;
		else
			return a.second >= b.second;
	} else
		return a.first >= b.first;
}

int main() {
	return 0;
}