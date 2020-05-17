#pragma once

#include "KeyHash.h"
#include "Node.h"
#include <iostream>
#include <vector>

using namespace std;

template <class K, class V, class F = KeyHash<K>>
class HashMap {
	Node<K, V>** arr;
	unsigned size;
	unsigned noOfKeys;
	F hashFunctor;
	
public:
	HashMap(unsigned = 1009);
	HashMap(const HashMap&);
	HashMap& operator=(const HashMap&);
	~HashMap();

	// adauga un element nou in HashMap
	void add(K, V);
	// returneaza true daca elementul este in HashMap
	bool search(K, V) const;
	// elimina un element din HashMap sau arunca exceptie daca nu exista
	void remove(K, V);

	// returneaza vector cu toate valorile pentru o cheie
	vector<V> valuesOf(K) const;
	// reeturneaza numarul de chei distincte
	unsigned getNoOfKeys() const;
	// returneaza prima valoare cunoscuta pentru o cheie
	V operator[](K);

	template <class K1, class V1, class F1>
	friend ostream& operator<<(ostream&, const HashMap<K1, V1, F1>&);
};

template <class K, class V, class F>
HashMap<K, V, F>::HashMap(unsigned size)
	: arr(new Node<K, V>* [size]), size(size), noOfKeys(0), hashFunctor(size) {
	for (unsigned i = 0; i < size; i++)
		arr[i] = NULL;
}

template <class K, class V, class F>
HashMap<K, V, F>::HashMap(const HashMap<K, V, F>& h)
	: arr(new Node<K, V>* [h.size]), size(h.size), noOfKeys(h.noOfKeys), hashFunctor(h.hashFunctor) {
	for (unsigned i = 0; i < h.size; i++) {
		if (h.arr[i] != NULL) {
			arr[i] = new Node<K, V>(h.arr[i]->key, h.arr[i]->values, h.arr[i]->prev, h.arr[i]->next);
			Node<K, V>* p = arr[i];
			Node<K, V>* q = h.arr[i];
			while (q != NULL) {
				if (q->next != NULL)
					p->next = new Node<K, V>(q->next->key, q->next->values, p, q->next->next);
				else
					p->next = NULL;
				p = p->next;
				q = q->next;
			}
		}
		else
			arr[i] = NULL;
	}
}

template <class K, class V, class F>
HashMap<K, V, F>::~HashMap() {
	for (unsigned i = 0; i < size; i++)
		if (arr[i] != NULL) {
			Node<K, V>* p = arr[i], * q = NULL;
			while (p != NULL) {
				q = p;
				p = p->next;
				delete q;
			}
		}
	delete[] arr;
}

template <class K, class V, class F>
void HashMap<K, V, F>::add(K key, V val) {
	unsigned index = hashFunctor(key);
	if (arr[index] == NULL) {
		vector<V> values;
		values.push_back(val);
		arr[index] = new Node<K, V>(key, values, NULL, NULL);
		noOfKeys++;
	}
	else {
		Node<K, V>* p = arr[index];
		while (p->next != NULL && p->key != key)
			p = p->next;
		if (p->key == key)
			p->values.push_back(val);
		else {
			vector<V> values;
			values.push_back(val);
			p->next = new Node<K, V>(key, values, p, NULL);
			noOfKeys++;
		}
	}
}

template <class K, class V, class F>
bool HashMap<K, V, F>::search(K key, V val) const {
	vector<V> v = valuesOf(key);
	for (const V& value : v)
		if (value == val)
			return true;
	return false;
}

template <class K, class V, class F>
void HashMap<K, V, F>::remove(K key, V val) {
	unsigned index = hashFunctor(key);
	Node<K, V>* p = arr[index];
	while (p != NULL && p->key != key)
		p = p->next;

	if (p == NULL)
		throw "Key not in table";

	if (p->values.size() > 1) {
		for (unsigned i = 0; i < p->values.size(); i++)
			if (p->values[i] == val) {
				p->values.erase(p->values.begin() + i);
				return;
			}
		throw "Value non-existent for key";
	}
	else {
		if (p->prev != NULL)
			p->prev->next = p->next;
		else
			arr[index] = p->next;

		if (p->next != NULL)
			p->next->prev = p->prev;

		delete p;
		noOfKeys--;
	}
}

template <class K, class V, class F>
vector<V> HashMap<K, V, F>::valuesOf(K key) const {
	unsigned index = hashFunctor(key);
	Node<K, V>* p = arr[index];
	while (p != NULL && p->key != key)
		p = p->next;
	if (p != NULL)
		return p->values;
	else {
		vector<V> emptyVector;
		return emptyVector;
	}
}

template <class K, class V, class F>
unsigned HashMap<K, V, F>::getNoOfKeys() const {
	return noOfKeys;
}

template<class K, class V, class F>
HashMap<K, V, F>& HashMap<K, V, F>::operator=(const HashMap& h) {
	if (&h == this)
		return *this;

	for (unsigned i = 0; i < size; i++)
		if (arr[i] != NULL) {
			Node<K, V>* p = arr[i], * q;
			while (p != NULL) {
				q = p->next;
				delete p;
				p = q;
			}
		}
	delete[] arr;

	arr = new Node<K, V>* [h.size];
	size = h.size;
	noOfKeys = h.noOfKeys;
	hashFunctor = h.hashFunctor;
	for (unsigned i = 0; i < size; i++)
		if (h.arr[i] != NULL) {
			arr[i] = new Node<K, V>(h.arr[i]->key, h.arr[i]->values, h.arr[i]->prev, h.arr[i]->next);
			Node<K, V>* p = arr[i];
			Node<K, V>* q = h.arr[i];
			while (q != NULL) {
				if (q->next != NULL)
					p->next = new Node<K, V>(q->next->key, q->next->values, p, q->next->next);
				else
					p->next = NULL;
				p = p->next;
				q = q->next;
			}
		}
		else
			arr[i] = NULL;

	return *this;
}

template <class K, class V, class F>
V HashMap<K, V, F>::operator[](K key) {
	vector<V> v = valuesOf(key);
	if (v.size() == 0)
		throw "Key not in table";
	return v[0];
}

template <class K1, class V1, class F1 = KeyHash<K1>>
ostream& operator<<(ostream& out, const HashMap<K1, V1, F1>& h) {
	for (unsigned i = 0; i < h.size; i++)
		if (h.arr[i] != NULL) {
			Node<K1, V1>* p = h.arr[i];
			while (p != NULL) {
				out << "(" << p->key << ": ";
				for (unsigned j = 0; j < p->values.size(); j++) {
					out << p->values[j];
					if (j < p->values.size() - 1)
						out << ", ";
				}
				out << ") ";
				p = p->next;
			}
		}
	return out;
}
