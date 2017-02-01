/* Working algorithm 3 "changedp".
Compile: g++ altCM.cpp -o alt -g -Wall
"valgrind --leak-check-full alt" checks good!
*/
#include <iostream>
using std::cout;
#include <climits>

// Prototypes.
int makeChange_3(int amount, int denoms[], int size, int minCoins[], int index[]);

int main() {
//	int denoms[] = { 1, 2, 4, 8 };				// Coin denominations.
//	int amount = 15;							// Amount of change to be given.
	int denoms[] = { 1, 3, 7, 12 };				// Coin denominations.
	int amount = 29;							// Amount of change to be given.
//	int amount = 31;							// Amount of change to be given.

	int size = sizeof(denoms) / sizeof(denoms[0]);
	int *minCoins = new int[amount + 1];			// Table of minumum coins solutions.
	int *index = new int[amount + 1];				// Table of indexes of coins used. 
	int *results = new int[size];					// Results array of all coins used for solution (repetitive).
	int *elem = new int[size];					// Coins used by frequency array.

	// Initialize elem to all 0's.
	for (int i = 0; i < size; i++) {
		elem[i] = 0;
	}

	// Determine minimum coins solution.
	int numCoins = makeChange_3(amount, denoms, size, minCoins, index);

	// Determine all coins used to make solution.
	int k = amount;
	int i = size;
	while (k) {
		results[i - 1] = denoms[index[k]];
		k -= denoms[index[k]];
		i--;
	}

	// Compare denoms[] to results[] and pouplate elem[] if match.
	for (int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++){
			if (denoms[i] == results[j]) {
				elem[i]++;
			}
		}
	}

	// Output header line.
	cout << "Algorithm changedp:\n";
	// Output denominations array.
	for (int i = 0; i < size; i++) {
		cout << denoms[i] << " ";
	}
	cout << '\n';

	// Output coins used array.
	for (int i = 0; i < size; i++) {
		cout << elem[i] << " ";
	}
	cout << '\n';

	//Output minimum coins total.
	cout << numCoins << '\n';

	// Memory management.
	delete[] minCoins;
	delete[] index;
	delete[] results;
	delete[] elem;

	return 0;
}

// Dynamic (Bottom-up) O(n^2) returns minimum coins required to make change. [1] [2]
int makeChange_3(int amount, int denoms[], int size, int minCoins[], int index[]) {
	minCoins[0] = 0;
	for (int j = 1; j <= amount; j++) {
		minCoins[j] = INT_MAX;
		for (int i = 0; i < size; i++) {
			if (j >= denoms[i] && 1 + minCoins[j - denoms[i]] < minCoins[j]) {
				minCoins[j] = 1 + minCoins[j - denoms[i]];
				index[j] = i;
			}
		}
	}
	return minCoins[amount];
}


/* CITATIONS: adapted from the following:
[1] http://condor.depaul.edu/rjohnson/algorithm/coins.pdf
[2] http://www.bogotobogo.com/Algorithms/dynamic_programming.php

*/