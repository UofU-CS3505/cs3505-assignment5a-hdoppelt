/**
 * @file trie.cpp
 * @brief Implementation of the Trie class for CS 3505 Assignment 4.
 * 
 * This file contains the implementation of a Trie.
 * 
 * A Trie efficiently stores and searches words while allowing fast retrieval of words 
 * that share common prefixes.
 * 
 * Features:
 * - Insert words into the Trie.
 * - Check if a word exists in the Trie.
 * - Find all words that start with a given prefix.
 * - Supports only lowercase letters ('a' to 'z').
 * 
 * This implementation includes:
 * - A default constructor for initialization.
 * - A copy constructor and assignment operator for deep copying.
 * - A destructor for proper memory management.
 * - Methods for adding and searching words.
 * 
 * @author Harrison Doppelt & Victor Valdez Landa
 * @date 02/12/2025
 */

#include "trie.h"
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::swap;

// Default Constructor
Trie::Trie() : isEndOfWord(false) {}

// Copy Constructor
Trie::Trie(const Trie& other) : children(other.children), isEndOfWord(other.isEndOfWord) {}

// Destructor
Trie::~Trie() {}

// Assignment Operator
Trie& Trie::operator=(Trie other) {
    if (this != &other) {
        isEndOfWord = other.isEndOfWord;
        children = other.children;
    }
    
    return *this;
}

// addWord
void Trie::addWord(const string& word) {
    Trie* currentNode = this;
    
    for (char letter : word) {  
        currentNode = &currentNode->children[letter];
    }
    
    currentNode->isEndOfWord = true;
}

// isWord
bool Trie::isWord(const string& word) const {

    if (word.empty()) {
        return false;
    }

    const Trie* currentNode = this;
    
    for (char letter : word) {

        if (letter < 'a' || letter > 'z') {
            return false;
        }

        auto childIterator = currentNode->children.find(letter);

        if (childIterator == currentNode->children.end()) {
            return false;
        }

        currentNode = &childIterator->second;
    }
    
    return currentNode->isEndOfWord;
}

// allWordsStartingWithPrefix
vector<string> Trie::allWordsStartingWithPrefix(const string& searchPrefix) const {

    // Start from the root node
    const Trie* currentNode = this;
    
    for (char letter : searchPrefix) {

        // Reject uppercase and non-alphabetic characters
        if (letter < 'a' || letter > 'z') {
            return {};      // Return an empty list
        }

        auto childIterator = currentNode->children.find(letter);
        if (childIterator == currentNode->children.end()) {
            return {};  // Prefix not found
        }

        currentNode = &childIterator->second;
    }
    
    // Vector to store found words
    vector<string> foundWords;

    // Stack to track Trie nodes for DFS traversal
    vector<const Trie*> nodeStack;

    // Stack to track the corresponding words during traversal
    vector<string> wordStack;

    // Push the starting node onto the stack
    nodeStack.push_back(currentNode);

    // Push the prefix onto the word stack
    wordStack.push_back(searchPrefix);
    
    // Continue traversal while stack is not empty
    while (!nodeStack.empty()) {

        // Get the last element from the stack
        const Trie* currentNode = nodeStack.back();

        // Get the corresponding word
        string currentWord = wordStack.back();

        // Remove the last element from the stack
        nodeStack.pop_back();

        // Remove the corresponding word
        wordStack.pop_back();
        
        // If this node marks the end of a word
        if (currentNode->isEndOfWord) {
            foundWords.push_back(currentWord);      // Add the word to the results
        }
        
        for (auto childIterator = currentNode->children.begin(); childIterator != currentNode->children.end(); ++childIterator) {
            nodeStack.push_back(&childIterator->second);
            wordStack.push_back(currentWord + childIterator->first);
        }
    }
    
    return foundWords;
}