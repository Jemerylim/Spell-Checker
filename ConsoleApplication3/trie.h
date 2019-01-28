#pragma once
#include <string>
#include <iostream>
#define CHAR_SIZE 128

using namespace std;

class trie
{
private:
	struct trieNode {
		bool eowFlag;  // this is to help the program know if the inserted or searched word is at the end. This helps seperate words during search. E.G seperating car and care as there is a flag.
		trieNode *child[CHAR_SIZE];  //creates an array of chars for my trie.
	};
	trieNode *root = new trieNode;



public:
	trie();
	void addtoTrie(string inputWord);
	bool searchTrie(string inputWord);
	bool checkLastNode();
};