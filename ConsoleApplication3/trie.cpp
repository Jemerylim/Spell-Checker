#include "pch.h"
#include "trie.h"


trie::trie() //makes all my node start of with a eowflag as false. 
{
	for (int i = 0; i < CHAR_SIZE; i++) {
		root->child[i] = NULL;
	}
	root->eowFlag = false;
}

void trie::addtoTrie(string inputWord) 
{
	// sets current node to root 
	// loop through the word taking a char a at a time
	trieNode *currentNode = root; 
	for (int i = 0; i < inputWord.length(); i++) 
	{
		// takes each char and minus a to get a index.
		// if this index does not exist, it means that this branch/ word has not been made 
		// it creates a new trie node to add the index of the char.
		// traverse to the next node
		//IF REACH THE END, SET End Of Word Flag to true.
		int in = inputWord[i] - 'a'; 
		if (inputWord[i] - 'a' < 0) in = 'a' - inputWord[i]; 
		if (currentNode->child[in] == NULL) { 

			currentNode->child[in] = new trieNode();
		}

		currentNode = currentNode->child[in];
	}
	currentNode->eowFlag = true;
}

// sets current node to root 
	// loop through the word taking a char a at a time
bool trie::searchTrie(string inputWord)
{
	trieNode *currentNode = root;

	for (int i = 0; i < inputWord.length(); i++)
	{

		//takes each char and minus a to get a index.
		//check input index with trie branches. if it is not inside ,
		//which means its NULL , the program will return false as teh word cannot be found.
		//traverse through the trie tree
		int in = inputWord[i] - 'a';
		if (currentNode->child[in] == NULL)
		{
			return false;
		}
		currentNode = currentNode->child[in];
	}
	// if there is no NULL and EOW is true means that the word is in the dictionary and thus returns true.
	return (currentNode != NULL && currentNode->eowFlag);
}

// check if there is still any more child below this node. 
// returns 1 if this is the last bottom node
bool trie::checkLastNode()
{
	for (int i = 0; i < CHAR_SIZE; i++)
		if (root->child[i])
			return 0;
	return 1;
}

