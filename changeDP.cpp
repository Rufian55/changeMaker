/******************************************************************************
* cs325-400-W17	Analysis of Algorithms	05 Feb 2017	Project 2
* Jonathan Horton	hortonjo@oregonstate.edu
* Chris Kearns		kearnsc@oregonstate.edu
* Dustin Pack		packdu@oregonstate.edu
*
* Program changeMaker.cpp reads an inputFile.txt file of space delimited ints
* that include the coin denominations available, sorted ascending, and a
* requested change amount. The program processes the data and appends the
* results to a seperate text file named inputFilechange.txt.
* Call from CLI: "makeChange inputFile.txt 1" to show with execution times,
*			  "makeChange inputFile.txt 0" otherwise.
* See makefile for compilation.
******************************************************************************/
#include "changeDP.hpp"

int main(int argc, char** argv) {
	if (argc < 2 || argc > 4 || atoi(argv[1]) < 0 || atoi(argv[1]) > 1) {
		cout << "Usage: \"changedp [input_file_name] 0\" or \"changedp "
			<< "[input_file_name] 1\"\n" 
			<< "0 for do not show execution times, 1 to show the exection times.\n";
		exit(1);
	}
	int showTime = 0;
	if (argc > 2) {
		showTime = atoi(argv[2]);
	}

	string theInputFile = argv[1];

	std::ifstream inputFile(theInputFile);

	vector<std::vector<int> > allData;	// 2D input vector.
	vector<std::vector<int> > results;	// 2d results vector.
	string eachLine;
	int eachInt;

	// Input the text file of ints to allData.
	while (std::getline(inputFile, eachLine)) {
		vector<int> lineData;		// 1D vector.
		std::stringstream inputStream(eachLine);

		while (inputStream >> eachInt) {
			// Add the ints from each line to the 1D vector.
			lineData.push_back(eachInt);
		}
		// Push the 1D vector onto the 2D vector as one "line".
		allData.push_back(lineData);
	}
	inputFile.close();

	string outputFile = argv[1];
	// Chop off ".txt" from argv[1] input string if .txt [1][2]
	if (outputFile.substr(outputFile.length() - 4, outputFile.length()) == ".txt") {
		outputFile.erase(outputFile.length() - 4);
	}
	outputFile = outputFile + "change.txt";

	// Algorithm 3 changedp.
	makeChange_3(allData, results, showTime, outputFile);

	return 0;
}


/* Dynamic (Bottom-up) O(nm) returns original denominations available, minimum coins
   required to make change and vector index for determining frequency of coins used in
   solution. [3][4] (Section 8.2.2) */
void makeChange_3(vector<vector<int> > allData, vector<vector<int> > &results, int showTime, string outputFile) {
	vector<int> denoms;			// Denominations of coins available.
	int amount;				// Amount of change to be given.
	vector<int> minCoins;		// Table of minumum coins solutions.
	vector<int> index;			// Table of indexes of coins used. 
	vector<int> localResults;	// Results array of all coins used for solution (repetitive).
	vector<int> elem;			// Coins used by frequency array.
							
	results.clear();			// Clear 2D results vector.

	// Process allData vector.
	for (unsigned int lineNum = 0; lineNum < allData.size(); lineNum += 2) {
		denoms.clear();
		minCoins.clear();
		index.clear();
		localResults.clear();
		elem.clear();

		denoms = allData[lineNum];
		amount = allData[lineNum + 1][0];
		int size = denoms.size();

		// Initialize index vectors for use in the makechangedp algorithm.
		for (int i = 0; i < allData[lineNum + 1][0] + 1; i++) {
			index.push_back(0);
		}

		// TIME FROM HERE...
		auto start = std::chrono::high_resolution_clock::now();

		minCoins.push_back(0);
		for (int j = 1; j <= amount; j++) {
			minCoins.push_back(INT_MAX);
			for (int i = 0; i < size; i++) {
				if (j >= denoms[i] && 1 + minCoins[j - denoms[i]] < minCoins[j]) {
					minCoins[j] = 1 + minCoins[j - denoms[i]];
					index[j] = i;
				}
			}
		}

		// Initialize localResults vectors for use in the makechangedp algorithm.
		for (int i = 0; i < size; i++) {
			elem.push_back(0);
		}

		auto end = std::chrono::high_resolution_clock::now();
		// ... TO HERE (line above).

		std::chrono::duration<double> execTime = end - start;

		if (showTime) {
			cout << std::fixed << std::setprecision(10) << "Elapsed time for algo_3 changedp, lineNum: "
				<< lineNum + 1 << " = " << execTime.count() << '\n';
		}

		if (CAPTURE_TIME == 1) {
			// Append timing data to timer.txt.
			std::ofstream timeFile("timer.txt", std::ios_base::app);
			timeFile << std::fixed << std::setprecision(10) << execTime.count() << '\n';
			timeFile.close();
		}

		// Build the 2D localResults vector.
		// Determine all coins used to make solution. [4] (Figure 8.2.2)
		int k = amount;
		while (k) {
			localResults.push_back(denoms[index[k]]);
			k -= denoms[index[k]];
		}

		// Compare denoms[] to localResults[] and populate elem[] if match.
		for (int i = 0; i < size; i++) {
			for (unsigned int j = 0; j < localResults.size(); j++) {
				if (denoms[i] == localResults[j]) {
					elem[i]++;
				}
			}
		}

		// Build the final results vector.
		results.push_back(denoms);			// The denominations (originally allData[lineNum]). 
		results.push_back(elem);				// The frequency of occurence.
		vector<int> solution;		
		solution.push_back(minCoins[amount]);
		results.push_back(solution);			// Minimum coins.
	}
	append2file(results, 3, outputFile);
}


// Uses stat() to check for file existence.
bool fileExists(string fileName) {
	struct stat buffer;
	return (stat(fileName.c_str(), &buffer) == 0);
}


// Appends results data to text file. //cout's are for testing.
void append2file(vector<vector<int> > &results, int z, string outputFile) {

	string algoName[3] = { "changeslow:", "changegreedy:", "changedp:" };

	// Open the results file for appending.
	std::ofstream resultFile(outputFile, std::ios_base::app);

	// Append "Algorithm: algoName[]" to resultFile.
	if (OK_2_DISPLAY_2_STDOUT == 1) {
		cout << "Algorithm ";
		cout << algoName[z - 1] << '\n';
	}
	else {
		resultFile << "Algorithm ";
		resultFile << algoName[z - 1] << '\n';
	}

	// Output results.  Change "cout" to "resultFile" via .hpp OK2SEND2STDOUT 1.
	for (unsigned int i = 0; i < results.size(); i++) {
		for (unsigned int j = 0; j < results[i].size(); j++) {
			if(OK_2_DISPLAY_2_STDOUT == 1){
				cout << results[i][j];
				cout << " ";
			}
			else {
				resultFile << results[i][j];
				resultFile << " ";
			}
		}

		if (OK_2_DISPLAY_2_STDOUT == 1) {
			cout << '\n';
		}
		else {
			resultFile << '\n';
		}
	}
	resultFile.close();
}


/* CITATIONS: Code adapted from the following sources:
[1] https://bytes.com/topic/c/answers/937279-delete-last-4-characters-given-string
[2] http://www.cplusplus.com/reference/string/string/at/
[3] http://condor.depaul.edu/rjohnson/algorithm/coins.pdf
[4] http://www.bogotobogo.com/Algorithms/dynamic_programming.php
*/