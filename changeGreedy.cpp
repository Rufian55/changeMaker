 /******************************************************************************
* cs325-400-W17	Analysis of Algorithms	05 Feb 2017	Project 2
* Jonathan Horton	hortonjo@oregonstate.edu
* Chris Kearns		kearnsc@oregonstate.edu
* Dustin Pack		packdu@oregonstate.edu
*
* Program changeMaker.cpp reads a text file of space delimited ints that include
* the coin denominations available, sorted ascending, and a requested change 
* amount. The program processes the data and appends the results to a seperate
* text file named inputFilechange.txt.
* Compile with: g++ changeMaker.cpp -o makeChange -g -Wall -std=c++11
* Call from CLI: "changeMaker inputFile.txt 1" to show with execution times,
* "changeMaker inputFile.text 0" otherwise.
* NOTE: Program will emit a warning if change requested > 30 due to excessively
* long processing times for the changeslow algorithm.
******************************************************************************/
#include "changeGreedy.hpp"
#define COLS 2 // Number of columns in data

int main(int argc, char** argv) {
	if (argc < 2 || argc > 4 || atoi(argv[1]) < 0 || atoi(argv[1]) > 1) {
		cout << "Usage: \"makeChange [input_file_name] 0\" or \"makeChange [input_file_name] 1\"\n" <<
			"0 for do not show execution times, 1 to show the exection times.\n";
		exit(1);
	}
	int showTime = 0;
	if (argc > 2) {
		showTime = atoi(argv[2]);
	}

	string theInputFile = argv[1];

	

	vector<std::vector<int> > allData;	// 2D input vector.
	vector<std::vector<int> > results;	// 2d results vector.
	string eachLine;
	int eachInt;

	// Input the text file of ints to allData.
    
    std::ifstream inputFile(theInputFile);
	while (std::getline(inputFile, eachLine)) {
		vector<int> lineData;		// 1D vector.
		std::stringstream inputStream(eachLine);
        
		while (inputStream >> eachInt) {
			// Add the ints from each line to the 1D vector.
			lineData.push_back(eachInt);
		}
		// Push the 1D vector onto the 2D vector as one "line".
		allData.push_back(lineData);
        //lineData.clear();
	}
	inputFile.close();
    
	string outputFile = argv[1];
	// Chop off ".txt" from argv[1] input string. [y]
	outputFile.erase(outputFile.length() - 4);	
	outputFile = outputFile + "change.txt";

	// Since we will have multiple write/append calls, we delete the old
	// inputFilechange.txt file first to ensure a "clean start".
	if (fileExists(outputFile)) {
		if (remove(outputFile.c_str()) != 0) { //[x]
			perror("Error deleting old inputFilechange.txt: ");
		}
	}

    //Call GreedyAlgorithm2
    greedyAlgorithm2(allData, results, showTime, outputFile);
    

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
void greedyAlgorithm2(vector<vector<int> > &allData, vector<vector<int> > &results, int showTime, string outputFile) {
    
    //BEGIN SETUP OF THE RESULTS VECTOR
    //Building with the end in mind we want to have a results vector that alternates in Denominations / Coins / NumberOfCoins
    vector<std::vector<int> > tempAllData(allData); //Make a copy of allData.  Use this in lieu of allData as we will be changing some values
    
    
    //First set up the results vector
    results.clear(); //Clear the Results Vector
    
    //Fill Results Vector with the denomination vectors from allData
    results = allData;
    
    //Create a second vector the same length as the first to hold 0 values.  This is ued to hold the coin count of each coin denomination
    for (int i = 0; i < results.size(); i++) {
        if (i % 2) {
            results[i][0] = 0;
            for (int j = 1; j < results[i-1].size(); j++) {
                results[i].push_back (0);
            }
        }
    }
    
    //Insert an index every 3 positions into the vector for total number of coins used
    std::vector<int> tempVector;
    tempVector.push_back(0);
    
    for (int i = 2; i < results.size()+1; i+= 3) {
        results.insert(results.begin()+i, tempVector);
    }
    
    //Insert an index into tempAllData so it aligns with the results vector
    for (int i = 2; i < allData.size()+1; i+= 3) {
        tempAllData.insert(tempAllData.begin()+i, tempVector);
    }
    //END SETUP OF RESULTS VECTOR

    //BEGIN GREEDY ALGORITHM
    for (int i = 0; i < results.size(); i+=3){
        // TIME FROM HERE...
        auto start = std::chrono::high_resolution_clock::now();
        
        
        //Iterate through the coin denominations
        for (int j = results[i].size()-1; j >= 0; j--) {
            //cout << results[i][j] << " ";
            if (results[i][j] <= tempAllData[i+1][0]) {
                results[i+1][j] = tempAllData[i+1][0]/results[i][j];  //posting the number of a particular coin to the results vector
                tempAllData[i+1][0] = tempAllData[i+1][0] - (results[i+1][j] * results[i][j]);   //Reduce target num by the number of coins * the value of the coin
                results[i+2][0] += results[i+1][j]; //Update the total number of coins
            }
        }
        
        // ...TO HERE
        auto end = std::chrono::high_resolution_clock::now();
        // ... TO HERE (line above).
        
        std::chrono::duration<double> execTime = end - start;
        //format and output the lines to show time
        if (showTime) {
            int line = i;
            if (line == 0) {
                line = 1;
            } else {
                line = (i /3)+1;
            }
            cout << std::fixed << std::setprecision(10) << "Elapsed time for algo_2 makechanggreedy, lineNum: "
            << line << " = " << execTime.count() << '\n';
        }
    }
    //END GREEDY ALGORITHM
    
    //Append the results file
    append2file(results, 2, outputFile);
}


// Uses stat() to check for file existence.
bool fileExists(string fileName) {
	struct stat buffer;
	return (stat(fileName.c_str(), &buffer) == 0);
}


// Appends results data to text file. //cout's are for testing.
void append2file(vector<vector<int> > &results, int z, string outputFile) {
    
	string algoName[3] = { "changeslow:", "changegreedy:", "changedp:" };

	// Open the results file for appending.	[6]
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
[1] http://condor.depaul.edu/rjohnson/algorithm/coins.pdf
[2] http://en.cppreference.com/w/cpp/chrono/high_resolution_clock/now
[3] http://stackoverflow.com/questions/17663186/initializing-a-two-dimensional-stdvector
[x] http://stackoverflow.com/questions/25778263/deleting-files-with-file-name
[y] https://bytes.com/topic/c/answers/937279-delete-last-4-characters-given-string

*/
