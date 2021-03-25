// Luke Anglin
// Feb 22
// lta9vw 
// wordPuzzle.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include "hashTable.h"
#include "timer.h"
using namespace std;


#define MAXROWS 500
#define MAXCOLS 500
char grid[MAXROWS][MAXCOLS];

// Forward declarations for GIVEN functions
bool readInGrid(string filename, int& rows, int& cols);
string getWordInGrid(int startRow, int startCol, int dir, int len,
	int numRows, int numCols);
bool checkprime(unsigned int p);
int getNextPrime(unsigned int n);
int rows, cols;

// Forward declarations for MY functions 
vector<string> words; // Words defined by the dictionary
string directions[8] = {"N ", "NE", "E ", "SE", "S ", "SW", "W ", "NW"};
void findWords(); 
vector<string> final_strings;
HashTable ht; 
timer t;
bool readInDict(string filename);
string formatOutput(int x, int y, int d, string word); // Formatter for final output 
bool isWord(string word); // Takes a word and if it's in the hash dictionary, returns true
int num_words;

int main(int argc, char **argv) {
	
	
	string grid_file = argv[2];
	string dict_file = argv[1];

    // Attempt to read in grid file
	bool grid_result = readInGrid(grid_file, rows, cols);

	// Attempt to read in dict file 
	bool dict_result = readInDict(dict_file);

    // If there is an error, report it
	if (!grid_result) {
		cout << "Error reading in grid file!" << endl;
		return 1;
	}
	if (!dict_result) {
		cout << "Error reading in grid file!" << endl;
		return 1;
	}

	ht = *(new HashTable(words.size()));
    // Check hash table insertion
	for (string word : words) ht.insert(word);
    // for (string word : ht) cout << word << endl;

		t.start();
	findWords();

	t.stop();
	// cout << "Found all words in " << (int)(t.getTime()*1000) << " milliseconds" << endl;
	cout << (int)(t.getTime()*1000) << endl;

	// Testing hash function

	// cout << "Hashing some words: " << test_ht.hash("Hello LUke") << endl;
	// cout << "Hashing some words: " << test_ht.hash("Hellfe") << endl;
	// cout << "Hashing some words: " << test_ht.hash("Hel LUke") << endl;



	// Testing hash insertion
	// test_ht.insert("Luke");
	// test_ht.insert("is");
	// test_ht.insert("cool");
	// cout << test_ht.find("Luke") << endl;
	// cout << test_ht.find("not_cool") << endl;

	return 0;
}

void findWords() {
	// We run along the columns until we reach the tr_x and tl_y 
	for (int x = 0; x < rows ; x++) { 

		// Run along the rows 
		for (int y = 0; y < cols ; y++){
			// Cout the current position (for dbg)
			// cout << "Current Position: (" << x << ", " << y << ")" << endl;

			// Loop lengths
			for (int l = 3; l < 23; l++) {

			// Loop directions
			// Insert the word at each position if its a word
				for (int d = 0; d < 8; d++) {
					// Try to insert. HT will deal with dups 
					string pot_word = getWordInGrid(x, y, d, l, rows, cols);
					// cout << pot_word << endl;

					// Check if it's a real word
					if (isWord(pot_word)) 
						final_strings.push_back(formatOutput(x, y, d, pot_word));	
					
				}				
			}

		}

	}
	// Remove duplicates from the final_strings 
	std::sort(final_strings.begin(), final_strings.end());
	auto it = unique(final_strings.begin(), final_strings.end());
	final_strings.resize(std::distance(final_strings.begin(), it));
	cout << final_strings.size() << " words found" << endl;
	for (string word : final_strings) 
		cout << word << endl;

}


string formatOutput(int x, int y, int d, string word) {
	// Formatting the direction
	string dir = directions[d];
	return (directions[d] + "(" + to_string(x) + ", " + to_string(y) + "):	" + word);
}


bool isWord(string word) {
	if (ht.find(word))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Gets the words from the word/dict file
bool readInDict(string filename) {
	// Attempt to open file 
	ifstream file(filename.c_str());

	// Upon error, msg
	if (!file.is_open()) {
		return false;
	}

	// If we're good, sweet. Read in words to our vector 
	string word;
	while (file >> word) {
		if (word.length() >= 3) words.push_back(word);
	}
	num_words = words.size(); // Set num words = to length of vector holding the words
	return true;
}

/** This function will read in a grid file, as per the format in the
 * CS 2150 lab 6 document, into a global grid[][] array.  It uses C++
 * file streams, and thus requires the the <fstream> #include header.
 *
 * @return true or false, depending on whether the file was
 *         successfully opened.
 * @param filename The file name to read in -- it's assumed to be in
 *                 the file format described in the lab document.
 * @param rows The number of rows as specified in the input file;
 *             as this is a reference, it is set by the function.
 * @param cols The number of columns as specified in the input file;
 *             as this is a reference, it is set by the function.
 */
bool readInGrid(string filename, int& rows, int& cols) {
    // try to open the file
	ifstream file(filename);
    // upon an error, return false
	if (!file.is_open()) {
		return false;
	}

    // first comes the number of rows
	file >> rows;
	// cout << "There are " << rows << " rows." << endl;

 //    // then the columns
	file >> cols;
	// cout << "There are " << cols << " cols." << endl;

    // and finally the grid itself
	string data;
	file >> data;

    // close the file
	file.close();

    // convert the string read in to the 2-D grid format into the
    // grid[][] array.
    // In the process, we'll print the grid to the screen as well.
    int pos = 0; // the current position in the input data
    for (int r = 0; r < rows; r++) {
    	for (int c = 0; c < cols; c++) {
    		grid[r][c] = data[pos++];
    		// cout << grid[r][c];
    	}
    	// cout << endl;
    }
    return true;
}

/** This function will retrieve a word in a grid of letters in a given
 * direction.  If the end of the grid is encountered before the length
 * of the desired string is reached, then a shorter string will be
 * returned.  The data is retrieved from a global char grid[][]
 * array, which is assumed to be defined (and in scope).  NOTE: The
 * return value is a static string variable (for efficiency
 * reasons), so a successive return value will overwrite a previous
 * return value.
 *
 * @return A STATIC string containing the letters in the provided direction.
 * @param startRow The starting (row,col) position to find the word.
 * @param startCol The starting (row,col) position to find the word.
 * @param dir The direction to move: 0 is north (upwards), 1 is
 *            northeast, and it rotates around clockwise until it
 *            reaches 7 for northwest.
 * @param len The desired length of the string to return (assuming
 *            the edge of the grid is not reached--if the edge of the
 *            grid is reached, it will return as many characters as
 *            possible up to the edge of the grid, so the returned
 *            string may not have the same length as this parameter
 *            indicates).
 * @param numRows The number of rows in the global char grid[][]
 *                array.
 * @param numCols The number of columns in the global char grid[][]
 *                array.
 */
string getWordInGrid (int startRow, int startCol, int dir, int len,
	int numRows, int numCols) {
    // the static-ness of this variable prevents it from being
    // re-declared upon each function invocation.  It also prevents it
    // from being deallocated between invocations.  It's probably not
    // good programming practice, but it's an efficient means to return
    // a value.
	static string output;
    output.clear(); // Since it's static we need to clear it
    output.reserve(256); // Can't set capacity in the constructor so do it the first time here

    // the position in the output array, the current row, and the
    // current column
    int r = startRow, c = startCol;
    // iterate once for each character in the output
    for (int i = 0; i < len; i++) {
        // if the current row or column is out of bounds, then break
    	if (c >= numCols || r >= numRows || r < 0 || c < 0) {
    		break;
    	}

        // set the next character in the output array to the next letter
        // in the grid
    	output += grid[r][c];

        // move in the direction specified by the parameter
        switch (dir) { // assumes grid[0][0] is in the upper-left
        	case 0:
        	r--;
                break; // north
                case 1:
                r--;
                c++;
                break; // north-east
                case 2:
                c++;
                break; // east
                case 3:
                r++;
                c++;
                break; // south-east
                case 4:
                r++;
                break; // south
                case 5:
                r++;
                c--;
                break; // south-west
                case 6:
                c--;
                break; // west
                case 7:
                r--;
                c--;
                break; // north-west
            }
        }

        return output;
    }


