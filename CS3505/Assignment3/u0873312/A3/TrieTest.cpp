// A3: Rule-Of-Three with a Trie
// Nick(Mykola) Pershyn
// CS3505 (CS5020)
#include <iostream>
#include <fstream>
#include <exception>

#include "Trie.h"


inline bool isAllowedCharcter(char c)
{
	return c >= 'a' && c <= 'z';
}

// checks whether word consists only from allowed characters
bool isValid(const std::string& word)
{
	for(std::string::const_iterator it = word.begin(); it < word.end(); ++it)
	{
		if(!isAllowedCharcter(*it))
			return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	//checking whether user have entered all the required arguments
	if(argc < 3)
	{
		std::cout << "Error! Number of parameters is too low!" << std::endl;
		std::cout << "Usage: ./TrieTest <words_file> <queries_file>" << std::endl;
		return 0;
	}

	//trying to open specified files and exit in case of failure
	std::ifstream words, queries;	// input file streams
	words.open(std::string(argv[1]), std::ifstream::in);
	queries.open(std::string(argv[2]), std::ifstream::in);
	if(words.is_open() == false)
	{
		std::cerr << "Error! Unable to open words file: " + std::string(argv[1]) << std::endl;
		return 0;
	}
	if(queries.is_open() == false)
	{
		std::cerr << "Error! Unable to open queries file: " + std::string(argv[2]) << std::endl;
		return 0;
	}

	Trie my_dictionary;
	std::string temp_word;			// temporary variable for read/add operations
	while(words >> temp_word)		// read the words till the stream is empty
	{
		if(isValid(temp_word))		// if there is something wrong with current word just notify the user and continue
			my_dictionary.addWord(temp_word);
		else
			std::cerr << "Warning! This word is not valid and is not added to the dictionary: " << temp_word << std::endl;
	}

	std::string temp_querie;		// temporary variable for read/check operations
	while(queries >> temp_querie)		// read the queries till the stream is empty
	{
		if(isValid(temp_querie))	// if there is something wrong with current querie just notify the user and continue checking
			if(my_dictionary.isWord(temp_querie))
				std::cout << temp_querie << " is found" << std::endl;
			else
			{
				std::cout << temp_querie << " is not found, did you mean:" << std::endl;
				auto temp = my_dictionary.allWordsWithPrefix(temp_querie);
				if(temp.size() > 0)
				for(const std::string& dictionaryWord : temp)
					std::cout << "   " << dictionaryWord << std::endl;
				else
					std::cout << "   no alternatives found" << std::endl;
			}
		else
			std::cerr << "Warning! This word is not valid and could not be in the dictionary: " << temp_querie << std::endl;
	}
	
	
	////////////////////////test
	Trie newDict(my_dictionary);
	temp_querie = "blah";		// temporary variable for read/check operations

		if(isValid(temp_querie))	// if there is something wrong with current querie just notify the user and continue checking
			if(newDict.isWord(temp_querie))
				std::cout << temp_querie << " is found" << std::endl;
			else
			{
				std::cout << temp_querie << " is not found, did you mean:" << std::endl;
				auto temp = newDict.allWordsWithPrefix(temp_querie);
				if(temp.size() > 0)
				for(const std::string& dictionaryWord : temp)
					std::cout << "   " << dictionaryWord << std::endl;
				else
					std::cout << "   no alternatives found" << std::endl;
			}
		else
			std::cerr << "Warning! This word is not valid and could not be in the dictionary: " << temp_querie << std::endl;
	///////
	return 0;
}
