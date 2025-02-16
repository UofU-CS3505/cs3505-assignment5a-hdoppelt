#ifndef TRIE_H
#define TRIE_H

/**
 * @file trie.h
 * @brief Definition of the Trie class for CS 3505 Assignment 4.
 * 
 * This header file defines the Trie class, which implements Trie for storing 
 * and searching words efficiently. 
 * 
 * It supports:
 * - Inserting words into the Trie.
 * - Checking if a word exists in the Trie.
 * - Finding all words that start with a given prefix.
 * 
 * The Trie only supports lowercase letters ('a' to 'z') and ignores uppercase and special characters.
 * 
 * @author Harrison Doppelt & Victor Valdez Landa
 * @date 02/12/2025
 */

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

/**
 * @class Trie
 * @brief A Trie for storing and searching words and prefixes.
 * 
 * This class provides word storage and retrieval.
 * 
 * It supports operations such as insertion, word search, and prefix-based search.
 */
class Trie {

private:

    // TODO COMMENT
    map<char, Trie> children;

    /** 
     * @brief Flag indicating whether this node represents the end of a valid word.
     * 
     * Set to `false` by default. Marked `true` only if a complete word ends at this node.
     */
    bool isEndOfWord;

public:

    /**
     * @brief Default Constructor
     * 
     * Initializes a new Trie node.
     * - Sets `isEndOfWord` to `false`.
     * - Initializes all children pointers to `nullptr`.
     */
    Trie();

    /**
     * @brief Copy Constructor
     * 
     * Creates a deep copy of another Trie, including all of its children.
     * 
     * Follows the Rule-Of-Three.
     * 
     * @param other The Trie instance to copy.
     */
    Trie(const Trie& other);

    /**
     * @brief Destructor
     * 
     * Recursively deletes all children and deallocates dynamically allocated memory.
     * 
     * Follows the Rule-Of-Three.
     */
    ~Trie();

    /**
     * @brief Assignment Operator
     * 
     * Implements the copy-and-swap idiom for safe assignment.
     * - Swaps data between the current instance and `other`.
     * - Ensures proper memory management.
     * 
     * Follows the Rule-Of-Three.
     * 
     * @param other The Trie instance to assign.
     * @return Reference to the assigned Trie object.
     */
    Trie& operator=(Trie other);

    /**
     * @brief Inserts a word into the Trie.
     * 
     * - Iterates through each character in the word.
     * - Creates new Trie nodes as needed.
     * - Marks `isEndOfWord = true` at the last character.
     * 
     * @param word The word to insert.
     */
    void addWord(const string& word);

    /**
     * @brief Checks if a given word exists in the Trie.
     * 
     * - Ignores empty words.
     * - Iterates through the Trie character by character.
     * - Rejects uppercase and non-alphabetic characters.
     * - Returns `true` if `isEndOfWord` is `true` at the last letter.
     * - Returns `false` if the word is not found or contains invalid characters.
     * 
     * @param word The word to search for.
     * @return `true` if the word exists, `false` otherwise.
     */
    bool isWord(const string& word) const;

    /**
     * @brief Finds all words that start with a given prefix.
     * 
     * - Locates the node where the prefix ends.
     * - Recursively collects all words that extend from this node.
     * - Returns a list of words that start with the prefix.
     * 
     * @param prefix The prefix to search for.
     * @return A vector of words that start with the given prefix.
     */
    vector<string> allWordsStartingWithPrefix(const string& prefix) const;
};

#endif