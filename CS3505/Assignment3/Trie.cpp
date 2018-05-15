// Assignment 3 Trie class by Tim Dorny u0829896.
// This class represents the Trie structure for word storage/retrieval.

#include "Trie.h"
using namespace std;

// Default Constructor
Trie::Trie(){
    root = TrieNode();
    size = 0;
}
// Copy constructor
Trie::Trie(const Trie& trie){
    root = TrieNode();
    root = trie.root;
    size = trie.size;

}
// Destructor
Trie::~Trie(){
    //delete root;
}

void Trie::addWord(string word){
    int sizeCheck = 0;
    // TrieNode reference to deal with TrieNode manipulation.
    TrieNode currentNode = root;
    for (char& c : word){
        // Determine array index from char value
        int index = c - 97;
        // Move to the next node in the trie, if null, a new one will be created
        currentNode = currentNode.getNextNode(index);
        sizeCheck++;


    }
    currentNode.setEndOfWord();
    // If word is longest in trie, set new size.
    if (sizeCheck > size){
        size = sizeCheck;
    }

}

bool Trie::isWord(string word){
    // Start with root node.
    TrieNode currentNode = root;
    // Variables to detect when word ends.
    int wordLength = word.length();
    int charCount = 1;
    // Check if word is contained in trie.
    for (char& c : word){
        int index = c - 97;
        if (currentNode.checkNextNode(index)){
            // If the char index is not null, we move to the next node.
            currentNode = currentNode.getNextNode(index);
        }
        // Once we hit the end of the nodes in trie, we check if we are at
        // the end of the word. If so, we return tru.
        else if(currentNode.isEndOfWord() && charCount == wordLength){
            return true;
        }
        // If the index is null and the end of the word has not been reached,
        // return false.
        else{
            // increment charCount
        charCount++;
        }
    }
    if (currentNode.isEndOfWord()){
        return true;
    }
    else{
        return false;
    }
}

vector<string> Trie::allWordsWithPrefix(string prefix){

    vector<string> words = vector<string>();
    TrieNode currentNode = root;
    //char build[size];

    // Move to node designated by prefix
    for (char& c : prefix){
        int index = c - 97;
        if (currentNode.checkNextNode(index)){
            currentNode = currentNode.getNextNode(index);
        }
        else{
            // If this code is reached, no words matching the given prefix found
            return words;
        }
    }
    if (currentNode.isEndOfWord()){
        words.push_back(prefix);
    }
    // Recursively add all words beginning with prefix to vector
    words = findPrefixWords(words, currentNode, prefix);
    return words;



}

vector<string> Trie::findPrefixWords(vector<string> words, TrieNode currentNode, string prefixString){
    for (int i = 0; i < 26; i++){
        if (currentNode.checkNextNode(i)){
            // Create new variables for node's string, node, etc for recursion
            TrieNode tempNode = currentNode.getNextNode(i);
            char letter = i + 97;
            string tempString = prefixString + letter;
            // If current node marks end of word, add it to vector
            if (currentNode.isEndOfWord()){
                words.push_back(tempString);
            }
            // Search new current node for extending words.
            findPrefixWords(words, tempNode, tempString);
        }
    }

    return words;
}
