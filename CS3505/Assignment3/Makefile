# Compiler and flags
CC = g++
CFLAGS = -Wall -std=c++11
TrieTest : TrieTest.cpp Trie.o TrieNode.o
	$(CC) $(CFLAGS) -o TrieTest TrieTest.cpp Trie.o TrieNode.o -lz

Trie.o : Trie.h Trie.cpp TrieNode.o
	$(CC) $(CFLAGS) -c Trie.cpp TrieNode.o -lz

TrieNode.o : TrieNode.h TrieNode.cpp
	$(CC) $(CFLAGS) -c TrieNode.cpp -lz

# Clean
clean :
	rm TrieTest *.o
