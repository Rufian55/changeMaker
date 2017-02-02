/******************************************************************************
* cs325-400-W17	Analysis of Algorithms	29 Jan 2017	Project 1
* Jonathon Horton	hortonjo@oregonstate.edu
* Chris Kearns		kearnsc@oregonstate.edu
* Dustin Pack		packdu@oregonstate.edu
*
* Program maxSumSubarray.hpp is the header file for maxSumSubarray.cpp
* Call from CLI: "maxSum 1" to show with execution times, "maxSum 0" otherwise.
* See makefile for compilation.
******************************************************************************/
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using std::cout;
#include <sys/stat.h>
#include <chrono>
#include <cstdlib>
#include <climits>
#include <limits>
#include <cstdio>
#include <ctime>

#define OK_2_DISPLAY_2_STDOUT 0

// Prototypes.
std::vector<int> AlGore1(std::vector<int> &V, int A);
int greedyAlgorithm2(int coins[], int m, int V);
int minCoins(int coins[], int m, int V);

bool fileExists(std::string fileName);
void append2file(std::vector<std::vector<int> > &results);
