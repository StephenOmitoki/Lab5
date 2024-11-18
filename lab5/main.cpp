#include <iostream>
#include <vector>
#include <string>

// Function k declaration and definition
template<class T>
T k(T i, T j) {
	return i + j;
}

// Template type definitions
template <class T>
using ELEM = std::vector<T>;

template <class T>
using VEC = std::vector<ELEM<T>>;

template <class T>
using action_t = T(*)(int);

template <class T>
using pred_t = bool(*)(T);

template <class T>
using map_t = T(*)(T, T);

// Function to print a single element
template <class T>
void printElem(ELEM<T> &v) {
	//std::cout << "[";
	for (size_t i = 0; i < v.size(); ++i) {
		std::cout << v[i];
		if (i != v.size() - 1) {
			std::cout << " , ";
		}
	}
	//std::cout << "]" << std::endl;

}

// Function to initialize a vector with a list of elements
template <class T>
void initVec(VEC<T> &v, ELEM<T> &&cons) {
	v.push_back(std::forward<ELEM<T>>(cons));
}

// Function to print a vector of elements
template <class T>
void printVec(VEC<T> &v) { std::cout << "[";
	for (auto &elem : v) {
	  
		printElem(elem);
	  std::cout << "]" << std::endl;
	}
}

// Function to generate a vector based on an action
template <class T>
VEC<T> generate(int N, action_t<T> f) {
	VEC<T> result;
	ELEM<T> elem;
	for (int i = 0; i < N; ++i) {

		elem.push_back(f(i));

	}
	result.push_back(elem);

	return result;
}

// Function to zip two vectors together
template <class T>
VEC<T> zip(VEC<T> &v, VEC<T> &w) {
	VEC<T> result;
	for (size_t i = 0; i < v.size(); ++i) {
		ELEM<T> elem;

		for (size_t j = 0; j < w[i].size(); ++j) {

			elem.push_back(v[i][j]);
			elem.push_back(w[i][j]);

		}

		result.push_back(elem);

	}
	return result;
}
// Function to filter a vector based on a predicate
template <class T>
VEC<T> filter(VEC<T> &v, pred_t<T> f) {
	VEC<T> result;
	for (auto &elem : v) {
		ELEM<T> filteredElem;
		for (auto &val : elem) {
			if (f(val)) {
				filteredElem.push_back(val);
			}
		}
		if (!filteredElem.empty()) {
			result.push_back(filteredElem);
		}
	}
	return result;
}

// Function to map an action onto a vector
template <class T>
VEC<T> map(VEC<T> &v, action_t<T> f) {
	VEC<T> result;
	for (auto &elem : v) {
		ELEM<T> mappedElem;
		for (auto &val : elem) {
			mappedElem.push_back(f(val));
		}
		result.push_back(mappedElem);
	}
	return result;
}

// Function to reduce a vector to a single element based on a mapping
template <class T>
ELEM<T> reduce(VEC<T> &v, map_t<T> f, ELEM<T> ident) {
	ELEM<T> result = ident;
	for (auto &elem : v) {
		for (auto &val : elem) {
			result[0] = f(result[0], val);
		}
	}
	return result;
}

// Example functions used in main
int f(int i) {
	return i * i;
}

bool g(int i) {
	return i > 0;
}

int h(int i) {
	return i > 0 ? 1 : 0;
}


int main()
{
	VEC<int> v;
	initVec(v, ELEM<int> {1,2,3,4});
	VEC<int> w;
	initVec(w, ELEM<int> {-1,3,-3,4});
	printVec(v);
	std::cout << std::string(10, '*') << std::endl;
	printVec(w);
	std::cout << std::string(10, '*') << std::endl;
	VEC<int> z = zip(v,w);
	printVec(z);
	std::cout << std::string(10, '*') << std::endl;
	VEC<int> x = zip(z,z);
	printVec(x);
	std::cout << std::string(10, '*') << std::endl;
	VEC<int> a = generate(10, f); // f is a function that squares
	printVec(a);
	VEC<int> y = filter(w, g); // g is a bool function that returns true if arg > 0
	printVec(y);
	VEC<int> u = map(w, h); // h is like g but returns 1 or 0
	printVec(u);
	ELEM<int> e = reduce(u, k, ELEM<int> {0});
	printElem(e);

	std::cout << std::endl << std::string(10, '$') << std::endl;
	VEC<std::string> ws;
	initVec(ws, ELEM<std::string> {"hello","there","franco","carlacci"});
	printVec(ws);
	ELEM<std::string> es = reduce(ws, k, ELEM<std::string> {""});
	printElem(es);

	VEC<char> wc;
	initVec(wc, ELEM<char> {'a','b','c','d'});
	std::cout << std::endl << std::string(10, '$') << std::endl;
	printVec(wc);
	ELEM<char> ec = reduce(wc, k, ELEM<char> {' '});
	std::cout << std::endl << std::string(10, '$') << std::endl;
	printElem(ec);

	return 0;
}
