######################################################################
# cs325-400-W17	Analysis of Algorithms	05 Feb 2017	Project 2
# Jonathon Horton	hortonjo@oregonstate.edu
# Chris Kearns		kearnsc@oregonstate.edu
# Dustin Pack		packdu@oregonstate.edu
# File: makefile
# Description: makefile for Make Change project.
# To execute the makefile on unix-y systems, type 'make all'.
######################################################################
CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -g

# Place a "#" in front of the line in default section that you wish to omit.

default:
	${CXX} ${CXXFLAGS} changeslow.cpp -o changeslow
	${CXX} ${CXXFLAGS} changeGreedy.hpp changeGreedy.cpp -o changegreedy
	${CXX} ${CXXFLAGS} changeDP.hpp changeDP.cpp -o changedp

all: changeslow.cpp changeGreedy.hpp changeGreedy.cpp changeDP.hpp changeDP.cpp
	${CXX} ${CXXFLAGS} changeslow.cpp -o changeslow
	${CXX} ${CXXFLAGS} changeGreedy.hpp changeGreedy.cpp -o changegreedy
	${CXX} ${CXXFLAGS} changeDP.hpp changeDP.cpp -o changedp

run: changeslow changegreedy changedp Amount.txt
	changeslow Amount.txt
	changegreedy Amount.txt
	changedp Amount.txt

clean:
	rm -f changeslow changegreedy changedp Amountchange.txt *.o *~