#pragma once

#include "KeyHash.h"
#include <vector>

using namespace std;

template <class K, class V>
class Node {
	K key;
	vector<V> values;
	Node<K, V>* prev, *  next;

	Node(K key, vector<V> values, Node<K, V>* prev, Node<K, V>* next)
		: key(key), values(values), prev(prev), next(next) {
	}

public:
	template<class K1, class V1, class F1>
	friend class HashMap;

	template <class K1, class V1, class F1>
	friend ostream& operator<<(ostream&, const HashMap<K1, V1, F1>&);
};
