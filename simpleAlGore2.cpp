/*******************************************************
 * CS325 Project 2 -- Algorithm 2 -- changegreedy
 * Group 20: Jonathan Horton, Dustin Pack, Chris Kearns
 * Compile: g++ alGore2.cpp -o greedy -g -Wall
 * Last Update: 2017-01-31
 *******************************************************/
#include <climits>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
using std::cout;
using std::endl;
using std::vector;

// Prototypes
int GreedyAlGore2(int coins[], int m, int V);

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: makeChange {int currency2Return}\n";
        exit(1);
    }
    int coins[] = { 50, 20, 10, 5, 2, 1 };		// U.K.
    int m = sizeof(coins) / sizeof(coins[0]);	// m is size of coins array (# of diff. coins)
    int V = atoi(argv[1]);
    cout << "Minimum coins required is " << GreedyAlGore2(coins, m, V) << '\n';
    return 0;
}


/***********************************************************************************
 *                         Algorithm 2: Greedy Algorithm (changegreedy)
 * This algorithm subtracts multiples of the largest value coin from the target value
 * then iterates to the next largest coin and repeats the process until the target is
 * reached.  From the Wikipedia Article on Greedy Algorithms it "looks to yield locally
 * optimal solutions in hopes of reaching a global solution.  This algorithm solves
 * all problems as long as the loest coin value = 1 but it will not optimally find the
 * minimum number of coins for all target numbers.
 ***********************************************************************************/

//V is the targetAmount
//m is size of coins[]
int GreedyAlGore2(int coins[], int m, int V) {
	
    
    
    int answerTable[m]; // we will later return this vector
    
    
    
    int numCoins = 0; //Holds Coin * Amount
    int targetAmount = V; //store parameter m as the targetAmount
    int endIndex = m; //set index to size of the vector for loop iteration control
    int currentIndex = 0;
    std::cout << endl;
    
    while (currentIndex < endIndex) {
        numCoins = targetAmount / coins[currentIndex];
        answerTable[currentIndex] = numCoins;
        targetAmount = targetAmount - (numCoins * coins[currentIndex]);
        std::cout << "Loop: " << currentIndex << " Number of  " << coins[currentIndex] << " coins: " << numCoins << std::endl;
        currentIndex = currentIndex + 1;
    }
	return 1; //fix return value here to return the array
}


/*
 Alternate pseudo code with a for loop (if while loop doesnt work)
 greedyChange(vector) 
    int targetNum = K
    int coins = [1, 2, 3, ..., k];
    int num = 0
 
    for (int i = 0; i < coin.length; i++) {
        if (coin[i] <=amount) {
            num = amount / coin[i];
            outputArray[i] = num
        }
 
 }
 
 */


