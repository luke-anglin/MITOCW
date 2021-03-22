// Name: Luke Anglin
// Date: 
// File: mathfun.cpp
// ID: lta9vw

/* 
PLANNING

Step 1 - Write out main, taking in 2 params.  CHECK
Step 2 - Get printing in correct format. CHECK 
Step 3 - Write c++ for function, and just comment it out once you've got the program working in assembly

C++ Code Below - product(int x, int y): 
*/

// int product(int x, int y) {
// 	// Initialize a local variable, i, to be the counter
// 	// And one to hold the current sum (end result will be product)
// 	int i = 0;
// 	int sum = 0; 
// 	// Loop through until i = y 
// 	while (i != y) {
// 		sum += x;
// 		i++;
// 	}
// 	return sum;
// }

// C++ Code below - power (int b, int n)

// int power(int b, int n) {
// 	// Base case - n = 0
// 	if (n == 0) return 1; 

// 	else { 
// 		return b * power(b, n-1);
// 	}
// }

extern "C" int product (int, int);
extern "C" int power (int, int);


#include <iostream> 
using namespace std;   



int main() {

	// Declare two vars for cin input 
	int int_1, int_2; 

	// Input from cin 
	cout << "Enter integer 1: "; 
	cin >> int_1;

	cout << "Enter integer 2: ";
	cin >> int_2;

	// cout << int_1 << int_2 << endl;
	cout << "Product: " << product(int_1, int_2) << endl;

	cout <<"Power: " << power(int_1, int_2) << endl;

	return 0;
}

