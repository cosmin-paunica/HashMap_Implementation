#include "HashMap.h"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

void tests();

int main() {
	tests();
	cout << "The tests have passed!" << endl;

	return 0;
}

void tests() {
	HashMap<string, int> h;

	// test metoda de adaugare + operator<<
	h.add("Cosmin", 4);
	h.add("Cosmin", 1);
	h.add("Alex", 3);
	h.add("Gelu", 7);
	cout << h << endl;

	// test metoda pt. obtinerea nr. de chei distincte
	assert(h.getNoOfKeys() == 3);

	// test metoda de cautare
	assert(h.search("Gelu", 7));
	assert(!h.search("Cosmin", 9));
	assert(!h.search("Gigi", 1));

	// test metoda ce intoarce vector cu valorile cunoscute pt. o cheie
	vector<int> v = { 4, 1 };
	assert(h.valuesOf("Cosmin") == v);

	// test metoda de stergere + obtinerea nr. de chei distincte
	h.remove("Alex", 3);
	assert(!h.search("Alex", 3));
	assert(h.getNoOfKeys() == 2);

	// test operator[]
	assert(h["Cosmin"] == 4);

	// test constructor de copiere
	HashMap<string, int> h1(h);
	h1.add("Mihai", 8);
	assert(h1.search("Mihai", 8) && !h.search("Mihai", 8));

	// test operator=
	HashMap<string, int> h2;
	h2 = h;
	h2.add("Ionel", 10);
	assert(h2.search("Ionel", 10) && !h.search("Ionel", 10));
}
