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
 * @author Harrison Doppelt
 * @date 02/06/2025
 */

#include "trie.h"
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::swap;

// Default Constructor
Trie::Trie() : isEndOfWord(false) {
    for (int i = 0; i < 26; i++) {
        children[i] = nullptr;
    }
}

// Copy Constructor
Trie::Trie(const Trie& other) {
    isEndOfWord = other.isEndOfWord;

    for (int i = 0; i < 26; i++) {

        // If the child exists in the other Trie
        if (other.children[i]) {
            children[i] = new Trie(*(other.children[i]));   // Create a new Trie node and recursively copy it
        } 

        // If there is no child at this position
        else {
            children[i] = nullptr;
        }
    }
}

// Destructor
Trie::~Trie() {
    for (int i = 0; i < 26; i++) {
        delete children[i];     // Delete each child node (calls their destructors recursively)
    }
}

// Assignment Operator
Trie& Trie::operator=(Trie other) {
    swap(isEndOfWord, other.isEndOfWord);
    swap(children, other.children);
    return *this;
}

void Trie::addWord(const string& word) {

    // Start from the root node
    Trie* node = this;
    
    for (char c : word) {  

        // Convert character to index (0-25)
        int index = c - 'a';
        
        // If node doesnt exist for this letter
        if (!node->children[index]) {  
            node->children[index] = new Trie();     // Create a new Trie node
        }
        
        // Move to the next node
        node = node->children[index];
    }
    
    // Mark the last node as the end of a valid word
    node->isEndOfWord = true;
}

bool Trie::isWord(const string& word) const {

    // Reject empty words
    if (word.empty()) {
        return false;
    }

    // Start from the root node
    const Trie* node = this;
    
    for (char c : word) {

        // Reject uppercase and non-alphabetic characters
        if (c < 'a' || c > 'z') {
            return false;
        }

        // Convert character to index (0-25)
        int index = c - 'a';

        // If node doesnt exist for this letter
        if (!node->children[index]) {
            return false;       // Word is not in Trie
        }

        // Move to the next character node
        node = node->children[index];
    }
    
    // Returns true if the last node marks the end of a word
    return node->isEndOfWord;
}

vector<string> Trie::allWordsStartingWithPrefix(const string& prefix) const {

    // Start from the root node
    const Trie* node = this;
    
    for (char c : prefix) {

        // Reject uppercase and non-alphabetic characters
        if (c < 'a' || c > 'z') {
            return {};      // Return an empty list
        }

        // Convert character to index
        int index = c - 'a';

        // If the prefix does not exist in Trie
        if (!node->children[index]) {
            return {};  // Return an empty list
        }

        // Move to the next node
        node = node->children[index];
    }
    
    // Vector to store found words
    vector<string> words;

    // Start with the given prefix
    string currentWord = prefix;

    // Stack to track Trie nodes for DFS traversal
    vector<const Trie*> nodeStack;

    // Stack to track the corresponding words during traversal
    vector<string> wordStack;

    // Push the starting node onto the stack
    nodeStack.push_back(node);

    // Push the prefix onto the word stack
    wordStack.push_back(currentWord);
    
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
        
        // Iterate over children in reverse order to maintain alphabetical order
        for (int i = 25; i >= 0; i--) {
            
            // If the child exists
            if (currentNode->children[i]) {
                nodeStack.push_back(currentNode->children[i]);  // Push it onto the stack for further traversal
                wordStack.push_back(word + char(i + 'a'));      // Append the character to the word and push to stack
            }
        }
    }
    
    return words;
}