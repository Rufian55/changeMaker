/******************************************************************************
* cs325-400-W17	Analysis of Algorithms	1 Feb 2017	Project 2
* Jonathon Horton	hortonjo@oregonstate.edu
* Chris Kearns		kearnsc@oregonstate.edu
* Dustin Pack		packdu@oregonstate.edu
*
* Program masterMakeChange.cpp reads a text file of space delimited ints and
* appends the Maximum Sum Subarray and sum of each line to a seperate text
* file. Compile with: g++ masterMakeChange.cpp -o makeChange -g -Wall -std=c++11
* Call from CLI: "makeChange 1" to show with execution times, "makeChange 0" otherwise.
******************************************************************************/

///////GLOBAL ISSUES TO FIX PRIOR TO SUBMISSION////////
/* [1]The output file should be [input filename]change.txt current output goes to hard
coded "AmountResults.txt"
 
 [2] update the description of algo3
 
 [3] update algo 2 to receive vector and return vector
 
 [4] update algo 3 to receive vector and return vector
*/


#include "masterMakeChange.hpp"

int main(int argc, char** argv) {
    // Check for proper usage
    if (argc < 2) {
        cout << "USAGE: " << argv[0] << " [inputFile].txt" << std::endl;
        cout << "(note that the .txt is not needed)" << std::endl;
        return 0;
    }

	// ***** Set up and Call Algorithm 1 *****
    
    // Open the file and start importing data
    std::ifstream inputFile;
    std::string filename = argv[1];
    std::string inFilename = filename + ".txt";
    inputFile.open(inFilename.c_str());
    
    // Can't find the file!
    if (!inputFile) {
        cout << "Cannot open file " << inFilename << std::endl;
        return 0;
    }
    
    // Open output file for writing data
    std::ofstream outputFile;
    filename += "change.txt";
    outputFile.open(filename.c_str());
    outputFile << "Algorithm changeslow:" << std::endl;
    
    std::string eachLine;
    int eachInt;
    int A;
    std::vector<int> V;
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
        
        
        // Timer from stackoverflow/questions/3220477/how-to-use-clock-in-c
        std::clock_t start;
        double duration;
        
        // Starting timer with call of algorithm
        start = std::clock();
        std::vector<int> coins = AlGore1(V, A);
        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        
        cout << "Duration: " << duration << std::endl;
        
        // Output data! (goes to screen and file appropriately)
        int numCoins = 0;
        cout << "Coin listing:" << std::endl;
        for (int count = 0; count < V.size(); count++) {
            cout << V[count] << " ";
            outputFile << V[count] << " ";
        }
        cout << std::endl;
        outputFile << std::endl;
        for (int count = 0; count < coins.size(); count++) {
            cout << coins[count] << " ";
            outputFile << coins[count] << " ";
            numCoins += coins[count];
        }
        cout << std::endl;
        outputFile << std::endl;
        cout << numCoins << std::endl;
        outputFile << numCoins << std::endl;
        std::cout << "help im in a loop!" << std::endl;
    }
    
    std::cout << "Now I'm not in a loop!" << std::endl;
    
    inputFile.close();
    outputFile.close();
	
    // ***** End Call to Algorithm 1 *****

    std::cout << "Program Ended Successfully" << std::endl;

	return 0;
}


/***********************************************************************************
 *                         Algorithm 1: Divide and Conquer (changeslow)
 * This algorithm will attempt to find the amount of change to minimize the number
 * of coins used. It will likely be slow. This works from the pseudocode given in
 * the statement of the assignment.
 ***********************************************************************************/
std::vector<int> AlGore1(std::vector<int> &V, int K) {
    std::vector<int> coins(V.size(), 0); // we will later return this vector
    
    // If there is a K-cent coin, then that one coin is the minimum.
    for (int count = 0; count < V.size(); count++) {
        if (V[count] == K) {
            coins[count]++;
            return coins;
        }
    }
    
    // Otherwise we have to recurse and search
    int minCoins = K + 1; // beyond maximum number of possible coins
    std::vector<int> savedCoins1(V.size(), 0);
    std::vector<int> savedCoins2(V.size(), 0);
    for (int i = 1; i < K; i++) { // notice i must start at 1!
        // Search every possible subset of change
        std::vector<int> tempCoins1 = AlGore1(V, i);
        std::vector<int> tempCoins2 = AlGore1(V, K - i);
        
        // Find the subsets that return the minimum number of coins
        int numCoins = 0;
        for (int count = 0; count < coins.size(); count++) {
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
    for (int count = 0; count < coins.size(); count++) {
        coins[count] += savedCoins1[count] + savedCoins2[count];
    }
    
    return coins;
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
int greedyAlgorithm2(int coins[], int m, int V) {
    
    
    
    int answerTable[m]; // we will later return this vector
    
    
    
    int numCoins = 0; //Holds Coin * Amount
    int targetAmount = V; //store parameter m as the targetAmount
    int endIndex = m; //set index to size of the vector for loop iteration control
    int currentIndex = 0;
    std::cout << std::endl;
    
    while (currentIndex < endIndex) {
        numCoins = targetAmount / coins[currentIndex];
        answerTable[currentIndex] = numCoins;
        targetAmount = targetAmount - (numCoins * coins[currentIndex]);
        std::cout << "Loop: " << currentIndex << " Number of  " << coins[currentIndex] << " coins: " << numCoins << std::endl;
        currentIndex = currentIndex + 1;
    }
    return 1; //fix return value here to return the array
}


/***********************************************************************************
 *                         Algorithm 3: Dynamic Programming (changedp)
 * This algorithm uses a table[] is indexed by values of change where table[v] is the
 * minimum number of coins needed to make change for v.
 ***********************************************************************************/
int minCoins(int coins[], int m, int V) {
    // table[i] will  store the minimum number of coins
    // required for i value, therefore table[V] is result.
    int table[V + 1];
    
    // Base case (If given value V is 0)
    table[0] = 0;
    
    // Initialize all table values EXCEPT table[0] as Infinite.
    for (int i = 1; i <= V; i++)
        table[i] = INT_MAX;
    
    // Compute min coins required for all values from 1 to V.
    for (int i = 1; i <= V; i++) {
        // Process all coins smaller than i.
        for (int j = 0; j < m; j++) {
            if (coins[j] <= i) {
                int sub_res = table[i - coins[j]];
                if (sub_res != INT_MAX && sub_res + 1 < table[i]) {
                    table[i] = sub_res + 1;
                }
            }
        }
    }
    return table[V];
}





// Uses stat() to check for file existence. [5]
bool fileExists(std::string fileName) {
	struct stat buffer;
	return (stat(fileName.c_str(), &buffer) == 0);
}


// Appends results data to text file. //cout's are for testing.
void append2file(std::vector<std::vector<int> > &results) {

	// Open the results file for appending.	[6]
	std::ofstream resultFile("Amount_Results.txt", std::ios_base::app);

	int skipLines = 0;
	// Test print results.  Change "cout" to "resultFile" for file writing.
	for (unsigned int i = 0; i < results.size(); i++) {
		skipLines++;
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

		if (skipLines % 3 == 0) {
			if (OK_2_DISPLAY_2_STDOUT == 1) {
				cout << '\n';
			}
			else {
				resultFile << '\n';
			}
		}
	}
	resultFile.close();
}


/******************************************************************************
* Helper functions below this line.
******************************************************************************/




/* CITATIONS: Code adapted from the following sources:
[0] http://condor.depaul.edu/rjohnson/algorithm/coins.pdf
[1] http://www.geeksforgeeks.org/find-minimum-number-of-coins-that-make-a-change/
[2] https://www.youtube.com/watch?v=FTmPXKh6O6o
*/
