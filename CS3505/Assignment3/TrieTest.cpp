// Assignment3 Test Class Tim Dorny u0829896

#include <string>
#include <iostream>
#include <fstream>
#include "Trie.h"
#include "TrieNode.h"

int main (int argc, char **argv){

    if (argc != 3){
        cout << "Invalid Arguments, try again." << endl;
        return 0;

    }
    cout << "1" << endl;

    // Filenames
    string file1 = argv[1];
    string file2 = argv[2];

    ifstream wordsToRead;
    wordsToRead.open(file1);
    ifstream wordsToCheck;
    wordsToCheck.open(file2);
    cout << "open files" << endl;
    if (!wordsToRead.is_open()){
        cout << "Unable to open words to read file." << endl;
        return 0;
    }
    cout << "dictionary open" << endl;
    if (!wordsToCheck.is_open()){
        cout << "unable to open words to check file." << endl;
    }
    cout << "checker open" << endl;
    // Put words from file into Trie
    Trie myTrie = Trie();
    cout << "trie created" << endl;
    string line;
    while(getline(wordsToRead, line)){
        myTrie.addWord(line);
    }
    cout << "added words to trie" << endl;
    wordsToRead.close();
    cout << "dictionary closed" << endl;
    while(getline(wordsToCheck, line)){
        if (myTrie.isWord(line)){
            cout << line << "is found!" << endl;
        }
        else {
            cout << line << "is not found, did you mean:" << endl;
        }
        // Get alternatives
        vector<string> suggestions = myTrie.allWordsWithPrefix(line);
        if (suggestions.size() == 0){
            cout << "   no alternatives found..." << endl;
        }
        else {
            for (string word : suggestions){
                cout << "   word" << endl;
            }
        }
    }
    wordsToCheck.close();
    cout << "finish" << endl;


}
