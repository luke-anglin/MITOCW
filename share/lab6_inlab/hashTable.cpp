// Luke Anglin
// Feb 22
// lta9vw 
// hashTable.cpp

#include "hashTable.h"
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;

HashTable::HashTable() {}
HashTable::~HashTable() {}

// Constructor
HashTable::HashTable(int num_words) {
	// Set table size to the rounded version of the number of words divided by the load factor 
	table_size = round(num_words / LOAD_FACTOR);

	// Ensure the table size is prime
	if (!checkprime(table_size)) table_size = getNextPrime(table_size);

	// Reserve space
	ht.reserve(table_size);

	// Set every spot equal to a list 
	list<string> l;
	for (int i{}; i < table_size; i++) {
		ht.push_back(l);
	}
}

unsigned int HashTable::hash(string word) {
	int sum{};
	unsigned int hashed;
	// For each char in the word, we'll sum up the ascii values and then modulo it 
	for (char chara : word) {
		sum += chara;
	}

	// Get hash by modulo'ing by table size 
	hashed = sum % table_size;
	return hashed;
}

// Inserts a word into vector of lists 
// In the event of a collision ()
bool HashTable::insert(string word) {
	try {
		unsigned int hashed = hash(word);
		list<string> & l = ht[hashed];
		l.push_back(word);
		if (l.size() > 1) l.unique();
		return true;
	}

	catch (int e) {
		cout << "Error inserting " << word << " with hash " << hash(word) << endl;
		cout << e << endl;
		return false;
	}
}


bool HashTable::find(string word) { 
	unsigned int hashed = hash(word);
	list<string> & l = ht[hashed];
	// 2 cases: It's in the list, or it isn't 
	bool isMember = (std::find(l.begin(), l.end(), word) != l.end());
	return isMember;

}


bool checkprime(unsigned int p) {
    if ( p <= 1 ) // 0 and 1 are not primes; the are both special cases
        return false;
    if ( p == 2 ) // 2 is prime
        return true;
    if ( p % 2 == 0 ) // even numbers other than 2 are not prime
        return false;
    for ( int i = 3; i*i <= p; i += 2 ) // only go up to the sqrt of p
        if ( p % i == 0 )
            return false;
    return true;
}
int getNextPrime (unsigned int n) {
    	while ( !checkprime(++n) );
    return n; // all your primes are belong to us
}

