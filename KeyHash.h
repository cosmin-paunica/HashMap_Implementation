#pragma once

#include <string>

using namespace std;

template <class K>
class KeyHash {
	unsigned arrSize;

	static string to_string(const string&);

public:
	KeyHash(unsigned);
	unsigned operator()(const K&) const;
};

template <class K>
string KeyHash<K>::to_string(const string& str) {
	return str;
}

template <class K>
KeyHash<K>::KeyHash(unsigned size) : arrSize(size) {
}

template <class K>
unsigned KeyHash<K>::operator()(const K& key) const {
	string str = to_string(key);
	unsigned code = 0;
	for (unsigned i = 1; i <= str.length(); i++)
		code += str[i-1];
	return code % arrSize;
}
