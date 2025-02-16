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
    Trie* node = this;
    
    for (char c : word) {  
        node = &node->children[c];
    }
    
    node->isEndOfWord = true;
}

// isWord
bool Trie::isWord(const string& word) const {

    if (word.empty()) {
        return false;
    }

    const Trie* node = this;
    
    for (char c : word) {

        if (c < 'a' || c > 'z') {
            return false;
        }

        auto it = node->children.find(c);

        if (it == node->children.end()) {
            return false;
        }

        node = &it->second;
    }
    
    return node->isEndOfWord;
}

// allWordsStartingWithPrefix
vector<string> Trie::allWordsStartingWithPrefix(const string& prefix) const {

    // Start from the root node
    const Trie* node = this;
    
    for (char c : prefix) {

        // Reject uppercase and non-alphabetic characters
        if (c < 'a' || c > 'z') {
            return {};      // Return an empty list
        }

        auto it = node->children.find(c);
        if (it == node->children.end()) {
            return {};  // Prefix not found
        }

        node = &it->second;
    }
    
    // Vector to store found words
    vector<string> words;

    // Stack to track Trie nodes for DFS traversal
    vector<const Trie*> nodeStack;

    // Stack to track the corresponding words during traversal
    vector<string> wordStack;

    // Push the starting node onto the stack
    nodeStack.push_back(node);

    // Push the prefix onto the word stack
    wordStack.push_back(prefix);
    
    // Continue traversal while stack is not empty
    while (!nodeStack.empty()) {

        // Get the last element from the stack
        const Trie* currentNode = nodeStack.back();

        // Get the corresponding word
        string word = wordStack.back();

        // Remove the last element from the stack
        nodeStack.pop_back();

        // Remove the corresponding word
        wordStack.pop_back();
        
        // If this node marks the end of a word
        if (currentNode->isEndOfWord) {
            words.push_back(word);      // Add the word to the results
        }
        
        for (auto it = currentNode->children.begin(); it != currentNode->children.end(); ++it) {
            nodeStack.push_back(&it->second);
            wordStack.push_back(word + it->first);
        }
    }
    
    return words;
}