// A3: Rule-Of-Three with a Trie
// Nick(Mykola) Pershyn
// CS3505 (CS5020)
#pragma once
#include <vector>
#include <string>

class Trie
{
private:
	Trie* root[26];		// Trie contains only one node - its root. It branches into subTries
	bool leaf;		// true if there is a word that has no further characters. An empty string for example
				// a word is represented by a path and final leaf
				// if "saw" is the only word in the dictionary, "sa" would be a valid path, but its leaf value would be false. So "sa" is not a word
public:
	~Trie();
	Trie();
	Trie(const Trie& other);		// copy constructor
	Trie& operator=(const Trie& other);	// assignment
	


	
	void addWord(const std::string& word);
	bool isWord(const std::string& word) const;
	std::vector<std::string> allWordsWithPrefix(const std::string& prefix) const;
};
