/*******************************************************
 * CS325 Project 2 -- Algorithm 1 -- changeslow
 * Group 20: Jonathan Horton, Dustin Pack, Chris Kearns
 * Last Update: 2017-02-02
 *
 * This algorithm will import a given .txt file with
 * given coin denominations and a target amount to find
 * in alternating lines. It's a slow, inefficient
 * algorithm that will struggle to find amounts > 30.
 *
 * To show full output, put "-verbose" after the file
 * name in the call to the program.
 *******************************************************/

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

// Prototype
vector<int> AlGore1(vector<int> &V, int A); 


/*******
 * main
 *******/
int main(int argc, char** argv) {
	
	// Check for proper usage
	if (argc < 2) {
		cout << "USAGE: " << argv[0] << " [inputFile].txt [-verbose]" << endl;
		return 0;
	}

	// Make sure the filename given is in the right form, chopping off .txt
	std::string filename = argv[1];
	if (filename.substr ( filename.length() - 4, filename.length() ) == ".txt")
		filename.erase(filename.length() - 4);

	// Open file for input
	std::ifstream inputFile;
	std::string inFilename = filename + ".txt";
	inputFile.open(inFilename.c_str());

	// Can't find the file!
	if (!inputFile) {
		cout << "Cannot open file " << inFilename << endl;
		return 0;
	}

	// Turning on optional output to the screen
	int verbose = 0;
	if (argc > 2)
		if (std::string(argv[2]).substr(0,2) == "-v")
			verbose = 1;

	// Open output file for writing data
	std::ofstream outputFile;
	filename += "change.txt";
	outputFile.open(filename.c_str(), std::ios_base::app);
	outputFile << "Algorithm changeslow:" << endl;

	std::string eachLine;
	int eachInt;
	int A;
	vector<int> V;
	// Take in one line and store coin values
	while(std::getline(inputFile, eachLine)) {
		V.clear();
		std::stringstream inputStream(eachLine);
		while(inputStream >> eachInt) {
			V.push_back(eachInt);
		}
		// Take in another line and store target amount A
		std::getline(inputFile, eachLine);
		std::stringstream inputStream2(eachLine);
		inputStream2 >> A;


		/*********************************************************************
		 * This is the limiter on the target amount, you can comment out this
		 * section if you want to try larger numbers.
		 *********************************************************************/
		if (A > 30) {
			cout << "WARNING: Target amount reduced from " << A << " to 30 for speed." << endl;
			A = 30;
		}
	
			
		// Timer from stackoverflow/questions/3220477/how-to-use-clock-in-c
		std::clock_t start;
		double duration;

		// Starting timer with call of algorithm
		start = std::clock();
		vector<int> coins = AlGore1(V, A); 
		duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

		if (verbose) { cout << "Duration: " << duration << " seconds" << endl; }

		// Output data! (goes to screen and file appropriately)
		int numCoins = 0;
		if (verbose) { cout << "Coin listing:" << endl; }
		for (unsigned int count = 0; count < V.size(); count++) {
			if (verbose) { cout << V[count] << " "; }
			outputFile << V[count] << " ";
		}
		if (verbose) { cout << endl; }
		outputFile << endl;
		for (unsigned int count = 0; count < coins.size(); count++) {
			if (verbose) { cout << coins[count] << " "; }
			outputFile << coins[count] << " ";
			numCoins += coins[count];
		}
		if (verbose) { cout << endl; }
		outputFile << endl;
		if (verbose) { cout << numCoins << endl; }
		outputFile << numCoins << endl;
	}

	inputFile.close();
	outputFile.close();
	return 0;
}


/***********************************************************************************
 *                         Algorithm 1: Divide and Conquer (changeslow)
 * 
 * Takes: vector of coin values, target amount to find change for.
 * Returns: vector of coins to use to get to target amount.
 *
 * This algorithm will attempt to find the amount of change to minimize the number
 * of coins used. It will likely be slow. This works from the pseudocode given in
 * the statement of the assignment.
 ***********************************************************************************/
vector<int> AlGore1(vector<int> &V, int K) {
	vector<int> coins(V.size(), 0); // we will later return this vector

	// If there is a K-cent coin, then that one coin is the minimum.
	for (unsigned int count = 0; count < V.size(); count++) {
		if (V[count] == K) {
			coins[count]++;
			return coins;
		}
	}

	// Otherwise we have to recurse and search
	int minCoins = K + 1; // beyond maximum number of possible coins
	vector<int> savedCoins1(V.size(), 0);
	vector<int> savedCoins2(V.size(), 0);
	// Reducing the range of i to just go to the halfway point still
	// finds values for every subset of change. Took me a while to notice.
	for (int i = 1; i <= (K/2); i++) { // notice i must start at 1!
		
		// Here, we could start keeping track of the results of every
		// recursion and return saved values to reduce calculation time.
		// Once we do that though, we get into the realm of
		// Dynamic Programming and it might invalidate the purpose
		// of the assignment.
		
		// Search every possible subset of change.
		vector<int> tempCoins1 = AlGore1(V, i);
		vector<int> tempCoins2 = AlGore1(V, K - i);

		// Find the subsets that return the minimum number of coins
		int numCoins = 0;
		for (unsigned int count = 0; count < coins.size(); count++) {
			numCoins += tempCoins1[count] + tempCoins2[count];
		}
		if (numCoins < minCoins) {	
			// save the minimum number of coins
			minCoins = numCoins;
			savedCoins1.swap(tempCoins1);
			savedCoins2.swap(tempCoins2);
		}
		
		// The minimum number of coins here is 2, so we can stop
		// the loop. This can save a lot of processing time.
		if (numCoins == 2) {
			i = K; // just a way to stop the loop
		}
	}

	// Reassemble our listing of saved coin amounts to return
	for (unsigned int count = 0; count < coins.size(); count++) {
		coins[count] += savedCoins1[count] + savedCoins2[count];
	}

	return coins;
}

