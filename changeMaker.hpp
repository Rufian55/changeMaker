/******************************************************************************
* cs325-400-W17	Analysis of Algorithms	05 Feb 2017	Project 2
* Jonathon Horton	hortonjo@oregonstate.edu
* Chris Kearns		kearnsc@oregonstate.edu
* Dustin Pack		packdu@oregonstate.edu
*
* Program changeMaker.hpp is the header file for changeMaker.cpp
* Call from CLI: "makeChange 1" to show with execution times, "makeChange 0"
otherwise.  See makefile for compilation.
******************************************************************************/
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <fstream>
#include <sstream>
#include <iostream>
using std::cout;
#include <iomanip>
#include <sys/stat.h>
#include <chrono>
#include <cstdlib>
#include <climits>
#include <numeric>

#define OK_2_DISPLAY_2_STDOUT 0

// Prototypes.
void makeChange_3(vector<vector<int> > &allData, vector<vector<int> > &results, int showTime, string outputFile);
bool fileExists(string fileName);
void append2file(vector<vector<int> > &results, int z, string outputFile);
