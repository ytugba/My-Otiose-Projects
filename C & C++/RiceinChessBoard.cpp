// ******************************************************************************************
// This program calculates the rice grains in a chess table(8 x 8). 
// The rule is: 1,2,4,8,16,32,64...2^n. Output will be the total number of squares we used.
// Because of 2^0, our max. 2^n must be 2^63. (63 + "2^0"'s square)
// If you do not have any rice, you need 0 square so output will be 0.
// ******************************************************************************************

#include <iostream>
using namespace std;

int main () {
	long double rice;

		while (cin >> rice) {
			if(rice <0) break;
			if(rice >=2) {

	long double next, previous = 1, sum = 1;
	int i = 1;

/*In while loop, calculation is like this: 
[1*2= 2, 1+2=3, previous = 2], [2*2=4,4+3=7, previous = 4]... */

				while(i <= 64) {

					next = previous * 2;
					sum += next;
					previous = next;

/*If loop calculates the number of squares that we need with counting method.*/	
				
				if (sum >= rice)
				{ cout << i+1 << endl; break; }
				++i; } }

			if (rice == 1) cout << "1" << endl;
			if (rice == 0) cout << "0" << endl; } 

return 0; }

// ******************************************************************************************
// Main Logic: Until the input number starting from 1 multiply every previous number with 2 and 
// increase the power of 2. Add special conditions for 0 and 1.
// ******************************************************************************************
