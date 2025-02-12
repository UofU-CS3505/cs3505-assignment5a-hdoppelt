# Name: Harrison Doppelt & Victor Valdez Landa
# Date: 02/12/2025
# Description: 	TODO...

# Compiler and flags
CC = g++
CFLAGS = -Wall
GOOGLETEST = 

# Compile Target
TrieTests: trie.o trieTests.o
	$(CC) $(CFLAGS) 

# Compile trie.o
trie.o: trie.cpp trie.h
	$(CC) $(CFLAGS) -c trie.cpp

# Compile trieTests.o
trieTests.o: trieTests.cpp trie.h
	$(CC) $(CFLAGS) -c trieTests.cpp

# Test target
test: 
	./trieTest