// Assignment 3 TrieNode Class, Tim Dorny u0829896
// This class represents the node objects used in the Trie implementation.
// C++ arrays are too hard for me apparently...

#include "TrieNode.h"
#include <algorithm>
#include <iostream>
using namespace std;


TrieNode::TrieNode(){
    cout << "pre array" << endl;
    // This line results in an infinite loop/seg fault, after many hours cursing my incompetence I have been unable to get it to wrk. ,,,, , , , , , , , , , ,
    nodes = new TrieNode[26];
    cout << "post array" << endl;
    endOfWord = false;
}
TrieNode::TrieNode(const TrieNode& trieNode){
    nodes = new TrieNode[26];
    nodes = trieNode.nodes;
    endOfWord = trieNode.endOfWord;
}
TrieNode::~TrieNode(){
    for (int i = 0; i < 26; i++){
        if (!(nodes[i].nodes == nullptr)){
            delete nodes[i].nodes;
        }
    }
}
TrieNode& TrieNode::operator=(TrieNode other){
    std::swap(nodes, other.nodes);
    std::swap(endOfWord, other.endOfWord);
    return *this;
}
bool TrieNode::isEndOfWord(){
    return endOfWord;
}
void TrieNode::setEndOfWord(){
    endOfWord = true;
}
TrieNode TrieNode::getNextNode(int index){

    // if (!nodes){
    //     nodes = new TrieNode[26];
    // }

    if (nodes[index].nodes == nullptr){
        nodes[index] = TrieNode();
        return nodes[index];
    }
    else{
        return nodes[index];
    }
}
bool TrieNode::checkNextNode(int index){
    if (nodes[index].nodes == nullptr){
        return false;
    }
    else{
        return true;
    }
}
