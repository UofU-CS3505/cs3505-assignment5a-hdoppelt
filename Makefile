# Name: Harrison Doppelt & Victor Valdez Landa
# Date: 02/18/2025
# Description:
#
#   This Makefile is used to compile and run unit tests for a Trie data structure
#   using GoogleTest.
#
# Targets:
# 	- TrieTests: Compiles and links the Trie implementation with GoogleTest.
#   - test: Runs the compiled TrieTests executable.
#   - clean: Removes compiled binaries and object files.

# Compiler and Flags
CC = g++
CFLAGS = -Wall

# GoogleTest Location
GOOGLETEST ?= googletest
GTEST_LIB = $(GOOGLETEST)/lib
GTEST_INC = $(GOOGLETEST)/googletest/include

# Compile Target
TrieTests: trie.o trieTests.o
	$(CC) $(CFLAGS) -L$(GTEST_LIB) -I$(GTEST_INC) trie.o trieTests.o -o TrieTests -lgtest -lgtest_main

# Compile trieTests.o
trieTests.o: trieTests.cpp trie.h
	$(CC) $(CFLAGS) -I$(GTEST_INC) -c trieTests.cpp

# Compile trie.o
trie.o: trie.cpp trie.h
	$(CC) $(CFLAGS) -c trie.cpp

# Test Target
test: TrieTests
	./TrieTests

# Clean Target
clean:
	rm -f TrieTests *.o