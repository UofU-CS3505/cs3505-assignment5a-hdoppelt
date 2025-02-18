/**
 * @file trie.cpp
 * @brief Implementation of the Trie class from CS 3505 Assignment 4.
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
 * @date 02/18/2025
 */

#include "trie.h"
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::swap;

Trie::Trie() : isEndOfWord(false) {}

Trie::Trie(const Trie& other) : children(other.children), isEndOfWord(other.isEndOfWord) {}

Trie::~Trie() {}

Trie& Trie::operator=(Trie other) {

    if (this != &other) {
        isEndOfWord = other.isEndOfWord;
        children = other.children;
    }

    return *this;
}

void Trie::addWord(const string& word) {
    Trie* currentNode = this;

    for (char letter : word) {
        currentNode = &currentNode->children[letter];
    }

    currentNode->isEndOfWord = true;
}

bool Trie::isWord(const string& word) const {
    const Trie* lastNode = traverseTrie(word);
    return lastNode != nullptr && lastNode->isEndOfWord;
}

vector<string> Trie::allWordsStartingWithPrefix(const string& searchPrefix) const {
    const Trie* lastNode = traverseTrie(searchPrefix);

    if (!lastNode) {
        return {};
    }
    
    vector<string> foundWords;
    vector<const Trie*> nodeStack = {lastNode};
    vector<string> wordStack = {searchPrefix};

    while (!nodeStack.empty()) {
        const Trie* currentNode = nodeStack.back();
        string currentWord = wordStack.back();
        nodeStack.pop_back();
        wordStack.pop_back();
        
        // If the current node is a vaid node, add it.
        if (currentNode->isEndOfWord) {
            foundWords.push_back(currentWord);
        }
        
        // Keep iterating through the letters of the Trie and push into the nodeStack, then update the wordStack.
        for (auto childIterator = currentNode->children.begin(); childIterator != currentNode->children.end(); ++childIterator) {
            nodeStack.push_back(&childIterator->second);
            wordStack.push_back(currentWord + childIterator->first);
        }
    }
    
    return foundWords;
}

bool Trie::isValidChar(char letter) {
    return letter >= 'a' && letter <= 'z';
}

const Trie* Trie::traverseTrie(const string& searchPrefix) const {
    const Trie* currentNode = this;

    for (char letter : searchPrefix) {

        if (!isValidChar(letter)) {
            return nullptr;
        }

        // Use maps find() to get or find the current letter
        auto childIterator = currentNode->children.find(letter);

        // Check If the current node points to the last element and theres nothing.
        if (childIterator == currentNode->children.end()) {
            return nullptr;
        }

        // Keep travversing through the Trie.
        currentNode = &childIterator->second;
    }

    return currentNode;
}