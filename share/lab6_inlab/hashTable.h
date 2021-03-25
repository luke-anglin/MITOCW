// Luke Anglin
// Feb 22
// lta9vw 
// hashTable.h

/* 

Potential Optimizations in future: 

1. Take advantage of max 22 char word 
2. Words which contain non-alphabetical chars may occur in dict but WONT be in a grid - only h_table needs
to handle them
3. 
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H
#define WORD_MAX 22 // Max amount of letters in a single word 
#define LOAD_FACTOR 0.75 // Therefore, table size should be 

#include <iostream>
#include <vector>
#include <list>
using namespace std;

class HashTable {

public:
	HashTable();
	HashTable(int num_words); // Creates a hash table of table size num_words / LOAD_FACTOR
	~HashTable();
	unsigned int table_size;
	vector< list<string> > ht; // Vector of vectors not ok, vector of Lists ok.

	 // MUST BE PRIME - I want this to resemble Java's hash table to prevent too much sep chaining, so I'll do a load factor of 0.75
	
	unsigned int hash(string word); // Hash function, takes a string and spits out an int
	bool insert(string word);
	bool find(string word); // Hashes the word, returns true if it's a word

};

bool checkprime(unsigned int p);
int getNextPrime(unsigned int n);












#endif 

