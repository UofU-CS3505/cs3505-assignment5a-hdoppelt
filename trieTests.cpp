/**
 * @file trieTests.cpp
 * @brief TODO...
 * @author Harrison Doppelt & Victor Valdez Landa
 * @date 02/12/2025
 */


// Basic cases (put information in, get information out)
// More unusual edge cases
// Trie copying and assignment behavior
// EXPECT_TRUE and EXPECT_EQ

#include "trie.h"
#include "gtest/gtest.h"
#include <iostream>
#include <cassert>

//=====ADDWORD===============

TEST(AddWord, CanAddWord) {

}



//=====ISWORD===============

TEST(IsWord, RejectEmptyWord) {

}

TEST(IsWord, RejectUppercaseWord) {

}

TEST(IsWord, RejectRandomUppercaseWord) {

}

TEST(IsWord, RejectSymbolWord) {

}

TEST(IsWord, AcceptValidWord) {

}



//=====ALLWORDSSTARTINGWITHPREFIX===============

TEST(AllWordsStartingWithPrefix, CanFindWordsWithPrefix) {

}

TEST(AllWordsStartingWithPrefix, CanNotFindWordsWithPrefix) {

}

TEST(AllWordsStartingWithPrefix, PrefixIsWord) {

}

TEST(AllWordsStartingWithPrefix, InvalidPrefix) {

}



//=====COPYCONSTRUCTOR/ASSIGNMENTOPERATOR===============

TEST(CopyConctructor, IsNotCopied) {
    
}

TEST(CopyConstructor, IsCopied) {

    Trie firstTrie;
    firstTrie.addWord("apple");

    Trie secondTrie(firstTrie);

    EXPECT_EQ(firstTrie.isWord("apple"), secondTrie.isWord("apple"));

}

TEST(EqualOperator, IsEqual){

    Trie firstTrie;
    firstTrie.addWord("apple");

    Trie secondTrie(firstTrie);

    firstTrie.addWord("banana");

    secondTrie = firstTrie;
    
    EXPECT_TRUE(secondTrie.isWord("banana"));
}



//=====DESTRUCTOR===============

TEST(Destructor, IsClearedFromMemory) {

}

TEST(Destructor, Works) {
    Trie* trie = new Trie();
    trie->addWord("hello");

    delete[] trie;

    EXPECT_TRUE(trie->isWord("hello"));
}