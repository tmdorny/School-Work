# A3: Rule-Of-Three with a Trie
# Nick(Mykola) Pershyn
# CS3505 (CS5020)
 
CC = g++
OPTS = -Wall -std=c++11 -O2
PROG = TrieTest

OBJS = Trie.o

all: $(PROG)

TrieTest: $(OBJS)
	$(CC) $(OPTS)    -o TrieTest TrieTest.cpp $(OBJS)

Trie.o:
	$(CC) $(OPTS) -c -o Trie.o Trie.cpp

test: $(PROG)
	./$(PROG) words queries

clean:
	rm -f *.o $(PROG)
