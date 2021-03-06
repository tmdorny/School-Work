#ifndef TRIENODE_IS_FUN
#define TRIENODE_IS_FUN

//#include <stdlib.h>
using namespace std;

class TrieNode {
    TrieNode* nodes;
    bool endOfWord;
public:
    TrieNode();
    TrieNode(const TrieNode& trieNode);
    ~TrieNode();
    TrieNode& operator=(TrieNode other);
    //void recursiveDelete(TrieNode node);
    char getChar();
    bool isEndOfWord();
    void setEndOfWord();
    TrieNode getNextNode(int index);
    bool checkNextNode(int index);

};
#endif
