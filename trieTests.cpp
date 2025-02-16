/**
 * @file trieTests.cpp
 * @brief TODO...
 * @author Harrison Doppelt & Victor Valdez Landa
 * @date 02/12/2025
 */

#include "trie.h"
#include "gtest/gtest.h"
#include <iostream>
#include <cassert>

TEST(AddWord, CanAddWord) {
    Trie trie;
    trie.addWord("hello");

    ASSERT_TRUE(trie.isWord("hello"));
}

TEST(AddWord, AddingShorterPrefixDoesNotRemoveLongerWord) {
    Trie trie;
    trie.addWord("apple");
    trie.addWord("app");

    ASSERT_TRUE(trie.isWord("apple"));
    ASSERT_TRUE(trie.isWord("app"));
}

TEST(IsWord, RejectEmptyWord) {
    Trie trie;

    ASSERT_FALSE(trie.isWord(""));
}

TEST(IsWord, RejectUppercaseWord) {
    Trie trie;
    trie.addWord("hello");

    ASSERT_FALSE(trie.isWord("Hello"));
}

TEST(IsWord, RejectRandomUppercaseWord) {
    Trie trie;
    trie.addWord("apple");

    ASSERT_FALSE(trie.isWord("aPpLe"));
}

TEST(IsWord, RejectSymbolWord) {
    Trie trie;
    trie.addWord("hello");

    ASSERT_FALSE(trie.isWord("hello!"));
}

TEST(IsWord, AcceptValidWord) {
    Trie trie;
    trie.addWord("valid");

    ASSERT_TRUE(trie.isWord("valid"));
}

TEST(AllWordsStartingWithPrefix, CanFindWordsWithPrefix) {
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

TEST(AllWordsStartingWithPrefix, CanNotFindWordsWithPrefix) {
    Trie trie;
    trie.addWord("banana");
    trie.addWord("grape");

    ASSERT_TRUE(trie.allWordsStartingWithPrefix("app").empty());
}

TEST(AllWordsStartingWithPrefix, PrefixIsWord) {
    Trie trie;
    trie.addWord("app");
    trie.addWord("apple");

    std::vector<std::string> words = trie.allWordsStartingWithPrefix("app");
    std::vector<std::string> expected = {"app", "apple"};

    ASSERT_EQ(expected, words);
}

TEST(AllWordsStartingWithPrefix, InvalidSymbolPrefix) {
    Trie trie;
    trie.addWord("word");

    ASSERT_TRUE(trie.allWordsStartingWithPrefix("!@#").empty());
}

TEST(AllWordsStartingWithPrefix, InvalidUppercasePrefix) {
    Trie trie;
    trie.addWord("word");

    ASSERT_TRUE(trie.allWordsStartingWithPrefix("Word").empty());
}

// ERROR
TEST(AllWordsStartingWithPrefix, EmptyPrefixReturnsAllWords) {
    Trie trie;
    trie.addWord("apple");
    trie.addWord("banana");
    trie.addWord("cherry");

    std::vector<std::string> words = trie.allWordsStartingWithPrefix("");
    std::sort(words.begin(), words.end());
    std::vector<std::string> expected = {"apple", "banana", "cherry"};

    ASSERT_EQ(expected, words);
}

TEST(CopyConstructor, IsCopied) {
    Trie firstTrie;
    firstTrie.addWord("apple");

    Trie secondTrie(firstTrie);

    ASSERT_TRUE(secondTrie.isWord("apple"));
}

TEST(CopyConstructor, CopyEmptyTrie) {
    Trie firstTrie;
    Trie secondTrie(firstTrie);

    ASSERT_FALSE(secondTrie.isWord("apple"));
}

TEST(CopyConstructor, ModificationsDoNotAffectOriginal) {
    Trie firstTrie;
    firstTrie.addWord("apple");

    Trie secondTrie(firstTrie);
    secondTrie.addWord("banana");

    ASSERT_FALSE(firstTrie.isWord("banana"));
}

TEST(AssignmentOperator, IsEqual) {
    Trie firstTrie;
    firstTrie.addWord("apple");

    Trie secondTrie;
    secondTrie = firstTrie;
    
    ASSERT_TRUE(secondTrie.isWord("apple"));
}

TEST(AssignmentOperator, ModificationsDoNotAffectOriginal) {
    Trie firstTrie;
    firstTrie.addWord("apple");

    Trie secondTrie;
    secondTrie = firstTrie;
    secondTrie.addWord("banana");

    ASSERT_FALSE(firstTrie.isWord("banana"));
}

TEST(AssignmentOperator, SelfAssignment) {
    Trie firstTrie;
    firstTrie.addWord("word");

    firstTrie = firstTrie;
    ASSERT_TRUE(firstTrie.isWord("word"));
}