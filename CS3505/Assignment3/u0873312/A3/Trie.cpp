// A3: Rule-Of-Three with a Trie
// Nick(Mykola) Pershyn
// CS3505 (CS5020) 

#include "Trie.h"

Trie::Trie()
{
	for(int i = 0; i < 26; ++i)
		root[i] = nullptr;
	leaf = false;
	return;
}

Trie::~Trie()
{
	// proper dealocation!
	// thanks you, valgrind for helping me to catch this :-)
	for(int i = 0; i < 26; ++i)
		if(root[i] != nullptr)
			delete root[i];		// calls destructor for earch subtree
	// do not dealocate root, since it is a fixed array!
}

Trie::Trie(const Trie& other)
{
	new (this) Trie;	// call the other constructor first
	for(auto& word : other.allWordsWithPrefix(""))
		this->addWord(word);
	return;
}

Trie& Trie::operator=(const Trie& other)
{
	if(this != &other)
	{
		*this = Trie(other);
	}
	return *this;
}

void Trie::addWord(const std::string& word)
{
	Trie* current = this;
	for(auto it = word.begin(); it < word.end(); ++it)
	{
		if(current->root[*it - 'a'] == nullptr)
			current->root[*it - 'a'] = new Trie;
		current = current->root[*it - 'a'];
	}
	current->leaf = true;
	return;
}
bool Trie::isWord(const std::string& word) const	// lookup does not modify the dictionary
{
	if(word == "")
		return false;

	Trie const* current = this;		// pointer to a constant Trie
	for(auto it = word.begin(); it < word.end(); ++it)
	{
		if(current->root[*it - 'a'] == nullptr)
			return false;			// if the path is not valid, there is no such word
		current = current->root[*it - 'a'];
	}
	return current->leaf;				// path is valid, but the word might not have been added. If added only the word "butterfly", the word "butt" should not be in the dictionary
}

std::vector<std::string> Trie::allWordsWithPrefix(const std::string& prefix) const
{
	std::vector<std::string> answer;
	if(prefix == "")	// get all the words in the dictionary
	{
		
		return std::vector<std::string>(3,"blah");
	}
	else			// get all the words in the subdictionary and add prefix to them
	{
		Trie const* subTrie = this;
		for(auto it = prefix.begin(); it < prefix.end(); ++it)
		{
			if(subTrie->root[*it - 'a'] == nullptr)
				return std::vector<std::string>(0);
			subTrie = subTrie->root[*it - 'a'];
		}
		for(const std::string& ending : subTrie->allWordsWithPrefix(""))
			answer.push_back(prefix + ending);
		return answer;
	}
	

}