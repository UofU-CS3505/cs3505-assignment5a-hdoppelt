/**
 * @file trieTests.cpp
 * @brief Tests for the modified Trie class from CS 3505 Assignment 4.
 * 
 * This file contains test cases for verifying the functionality of the modified Trie class.
 * 
 * The tests cover:
 *  - Word insertion and retrieval.
 *  - Handling of invalid inputs (uppercase, symbols, empty strings).
 *  - Prefix-based word searching.
 *  - Copy constructor and assignment operator.
 *  - Partitions, Boundaries, and Edge cases.
 * 
 * Uses Google Test (`gtest/gtest.h`) for assertions.
 * 
 * @author Harrison Doppelt & Victor Valdez Landa
 * @date 02/18/2025
 */

#include "trie.h"
#include "gtest/gtest.h"
#include <iostream>
#include <cassert>

/**
 * @brief Test: Adding a word to the Trie.
 * 
 * Ensures that a word can be successfully inserted and later found.
 */
TEST(AddWordTest, CanAddWord) {
    Trie trie;
    trie.addWord("hello");

    ASSERT_TRUE(trie.isWord("hello"));
}

/**
 * @brief Test: Adding a shorter word that is a prefix of an existing word.
 * 
 * Ensures that inserting "app" after "apple" does not remove "apple".
 */
TEST(AddWordTest, AddingShorterPrefixDoesNotRemoveLongerWord) {
    Trie trie;
    trie.addWord("apple");
    trie.addWord("app");

    ASSERT_TRUE(trie.isWord("apple"));
    ASSERT_TRUE(trie.isWord("app"));
}

/**
 * @brief Test: Reject empty word insertion.
 * 
 * Ensures that an empty string is not recognized as a valid word.
 */
TEST(IsWordTest, RejectEmptyWord) {
    Trie trie;

    ASSERT_FALSE(trie.isWord(""));
}

/**
 * @brief Test: Reject uppercase words.
 * 
 * Ensures that words with uppercase letters are not considered valid.
 */
TEST(IsWordTest, RejectUppercaseWord) {
    Trie trie;
    trie.addWord("hello");

    ASSERT_FALSE(trie.isWord("Hello"));
}

/**
 * @brief Test: Reject mixed-case words.
 * 
 * Ensures that words containing a mix of uppercase and lowercase letters are rejected.
 */
TEST(IsWordTest, RejectRandomUppercaseWord) {
    Trie trie;
    trie.addWord("apple");

    ASSERT_FALSE(trie.isWord("aPpLe"));
}

/**
 * @brief Test: Reject words containing symbols.
 * 
 * Ensures that words with special characters (e.g., "!") are not valid.
 */
TEST(IsWordTest, RejectSymbolWord) {
    Trie trie;
    trie.addWord("hello");

    ASSERT_FALSE(trie.isWord("hello!"));
}

/**
 * @brief Test: Accept a valid lowercase word.
 * 
 * Ensures that a correctly formatted word is stored and found.
 */
TEST(IsWordTest, AcceptValidWord) {
    Trie trie;
    trie.addWord("valid");

    ASSERT_TRUE(trie.isWord("valid"));
}

/**
 * @brief Test: Find all words that start with a given prefix.
 * 
 * Ensures that words with a common prefix are returned.
 */
TEST(AllWordsStartingWithPrefixTest, CanFindWordsWithPrefix) {
    Trie trie;
    trie.addWord("apple");
    trie.addWord("applet");
    trie.addWord("applause");

    std::vector<std::string> words = trie.allWordsStartingWithPrefix("app");
    std::sort(words.begin(), words.end());
    std::vector<std::string> expected = {"apple", "applet", "applause"};
    std::sort(expected.begin(), expected.end());

    ASSERT_EQ(expected, words);
}

/**
 * @brief Test: No words found for a nonexistent prefix.
 * 
 * Ensures that searching for a prefix not present in the Trie returns an empty list.
 */
TEST(AllWordsStartingWithPrefixTest, CanNotFindWordsWithPrefix) {
    Trie trie;
    trie.addWord("banana");
    trie.addWord("grape");

    ASSERT_TRUE(trie.allWordsStartingWithPrefix("app").empty());
}

/**
 * @brief Test: Prefix itself is a word.
 * 
 * Ensures that if a prefix is a full word, it is included in the results.
 */
TEST(AllWordsStartingWithPrefixTest, PrefixIsWord) {
    Trie trie;
    trie.addWord("app");
    trie.addWord("apple");

    std::vector<std::string> words = trie.allWordsStartingWithPrefix("app");
    std::vector<std::string> expected = {"app", "apple"};

    ASSERT_EQ(expected, words);
}

/**
 * @brief Test: Rejects invalid symbol prefixes.
 * 
 * Ensures that special characters as prefixes return an empty result.
 */
TEST(AllWordsStartingWithPrefixTest, InvalidSymbolPrefix) {
    Trie trie;
    trie.addWord("word");

    ASSERT_TRUE(trie.allWordsStartingWithPrefix("!@#").empty());
}

/**
 * @brief Test: Rejects uppercase prefixes.
 * 
 * Ensures that searching with an uppercase prefix returns no results.
 */
TEST(AllWordsStartingWithPrefixTest, InvalidUppercasePrefix) {
    Trie trie;
    trie.addWord("word");

    ASSERT_TRUE(trie.allWordsStartingWithPrefix("Word").empty());
}

/**
 * @brief Test: Empty prefix returns all stored words.
 * 
 * Ensures that an empty prefix fetches all words in the Trie.
 */
TEST(AllWordsStartingWithPrefixTest, EmptyPrefixReturnsAllWords) {
    Trie trie;
    trie.addWord("apple");
    trie.addWord("banana");
    trie.addWord("cherry");

    std::vector<std::string> words = trie.allWordsStartingWithPrefix("");
    std::sort(words.begin(), words.end());
    std::vector<std::string> expected = {"apple", "banana", "cherry"};

    ASSERT_EQ(expected, words);
}

/**
 * @brief Test: Copy constructor correctly duplicates Trie.
 * 
 * Ensures that the copied Trie retains inserted words.
 */
TEST(CopyConstructorTest, IsCopied) {
    Trie firstTrie;
    firstTrie.addWord("apple");

    Trie secondTrie(firstTrie);

    ASSERT_TRUE(secondTrie.isWord("apple"));
}

/**
 * @brief Test: Copy constructor for an empty Trie.
 * 
 * Ensures that an empty Trie remains empty after copying.
 */
TEST(CopyConstructorTest, CopyEmptyTrie) {
    Trie firstTrie;
    Trie secondTrie(firstTrie);

    ASSERT_FALSE(secondTrie.isWord("apple"));
}

/**
 * @brief Test: Copy constructor ensures deep copy.
 * 
 * Ensures that modifying the copied Trie does not affect the original.
 */
TEST(CopyConstructorTest, ModificationsDoNotAffectOriginal) {
    Trie firstTrie;
    firstTrie.addWord("apple");

    Trie secondTrie(firstTrie);
    secondTrie.addWord("banana");

    ASSERT_FALSE(firstTrie.isWord("banana"));
}

/**
 * @brief Test: Assignment operator correctly assigns Trie contents.
 * 
 * Ensures that assigning one Trie to another correctly transfers words.
 */
TEST(AssignmentOperatorTest, IsEqual) {
    Trie firstTrie;
    firstTrie.addWord("apple");

    Trie secondTrie;
    secondTrie = firstTrie;
    
    ASSERT_TRUE(secondTrie.isWord("apple"));
}

/**
 * @brief Test: Assignment operator ensures deep copy.
 * 
 * Ensures that modifying the assigned Trie does not affect the original.
 */
TEST(AssignmentOperatorTest, ModificationsDoNotAffectOriginal) {
    Trie firstTrie;
    firstTrie.addWord("apple");

    Trie secondTrie;
    secondTrie = firstTrie;
    secondTrie.addWord("banana");

    ASSERT_FALSE(firstTrie.isWord("banana"));
}

/**
 * @brief Test: Self-assignment safety.
 * 
 * Ensures that assigning a Trie to itself does not corrupt its data.
 */
TEST(AssignmentOperatorTest, SelfAssignment) {
    Trie firstTrie;
    firstTrie.addWord("word");

    firstTrie = firstTrie;
    ASSERT_TRUE(firstTrie.isWord("word"));
}