#ifndef TRIE_IS_FUN
#define TRIE_IS_FUN

#include "TrieNode.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Trie {
    TrieNode root;
    int size;
public:
    Trie();
    Trie(const Trie& trie);
    ~Trie();
    // assignment=
    void addWord (string word);
    bool isWord (string word);
    vector<string> allWordsWithPrefix(string words);
    vector<string> findPrefixWords(vector<string> words, TrieNode currentNode, string prefixString);

};
#endif
