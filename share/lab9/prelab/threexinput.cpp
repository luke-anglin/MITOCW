// Luek Anglin
// Date: 
// lta9vw
// threexinput.cpp


#include <iostream>
#include "timer.h"
using namespace std;

int steps;

// int threexplusone(int x) {
// 	// Is it one?
// 	if (x == 1) return steps;

// 	// Is it even?
// 	if (x % 2 == 0) {
// 		steps+=1; 
// 		x = x/2;
// 		return threexplusone(x);
// 	}
// 	else {
// 		steps += 1;
// 		x = 3*x + 1;
// 		return threexplusone(x);
// 	}
// }

extern "C" int threexplusone(int x); 

int main() {
	// Default value of 0 for paramas
	// x is collatz num
	// n is number of times to call subroutine
	int x, n = 0;
	// Ask for input
	cout << "Enter a number: ";
	cin >> x;
	cout << "Enter iterations of subroutine: ";
	cin >> n;

	cout << "Steps: " << threexplusone(x) << endl;
	// create timer
	timer t;
	t.start();
	for (int i = 0; i < n ; i++) threexplusone(x);
	t.stop();
	// cout << "Time to run " << n << " iterations: " <<  t.getTime()*1000 << "ms" << endl;
	return 0;
}