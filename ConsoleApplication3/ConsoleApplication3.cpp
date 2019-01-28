// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include "pch.h"

#include "trie.h"
#include <fstream>

using namespace std;

//Jeremy Lim S10179911B
// Yong Kang s10177465



//This will be loops to display menu for user to see
void startMenu() {
	cout << "Spell Checker" << endl;
	cout << endl;
	cout << " [1] Check a Word" << endl;
	cout << " [2] Check a file" << endl;
	cout << " [3] Add New Word to Dictionary" << endl;
	cout << " [4] Save dictionary to file" << endl;
	cout << " [5] Show all words starting with Letter" << endl;
	cout << " [6] Spell check a word (Addition/Transposition)" << endl;
	cout << " [0] Exit" << endl;
	cout << "Enter Option" << endl;
	cout << endl;
}
// clears screens and ask for users input on a word
string option1() {
	system("CLS");
	cout << " Check a Word" << endl;
	cout << " Enter a word :";
	string input;
	cin >> input;
	return input;
}
// clears screens and ask for users input on a file that is TXT
string option2() {
	system("CLS");
	cout << " Check a file" << endl;
	cout << " Enter a file with file type (.txt) :";
	string input;
	cin >> input;
	return input;
}

// clears screens and ask for users input on a word
string option3() {
	system("CLS");
	cout << " Add a word" << endl;
	cout << " Enter a word to add:";
	string input;
	cin >> input;
	return input;
}
// Saves the current Dictionary to a file.
bool option4() {
	system("CLS");
	cout << " Save the dictionary" << endl;
	ifstream inFile2;
	inFile2.open("dictionary.txt");
	ofstream myfile;
	myfile.open("dictionary1.txt");
	string word;
	while (getline(inFile2, word))
	{
		myfile << word << endl;
	}
	myfile.close();
	inFile2.close();
	return true;
}

// clears screens and ask for users input on a prefix and the program will show all words with that prefix.
string option5() {
	system("CLS");
	cout << " Show all words starting with ..." << endl;
	cout << " Enter a prefix:";
	string input;
	cin >> input;
	
	return input;
}

// clears screens and ask for users input on a word and program will check if its valid.
string option6() {
	system("CLS");
	cout << " Check a word (Error allowed) " << endl;
	cout << " Enter a word to Check:";
	string input;
	cin >> input;
	return input;
}

int main()
{

	trie trie;
	ifstream inFile;
	inFile.open("dictionary.txt");
	string word;
	string line;

	while (getline(inFile, word)) // adds all dictionary words to the trie.
	{
		trie.addtoTrie(word);
	}
	cout << "Dictionary Loaded" << endl;
	inFile.close();

	bool loopCon = true;

	while (loopCon == true) {

		startMenu();
		int input;
		cin >> input;

		// if inputted word is in the trie which can be found out using searchTrie,
		//it will display word in the trie.
		if (input == 1) { 
			string in;
			in = option1();
			bool in_trie = trie.searchTrie(in);
			if (in_trie == true) {
				cout << in << " " << "is in the dictionary" << endl;
			}
			else
			{
				cout << in << " " << "is not in the dictionary" << endl;
			}

		}

		//checks for the validity of the file
		//after it is valid, run every word against the dictionary and print out only WRONG words.
		else if (input == 2) {
			ifstream inFile1;
			string in = option2();
			inFile1.open(in);
			if (!inFile1.is_open()) {
				cout << "No such file!" << endl;
			}
			else
			{
				string ranWord;
				bool in_trie = false;
				while (getline(inFile1, ranWord))
				{
					int i = 0;
					while (i <= ranWord.length())
					{
						ranWord[i] = tolower(ranWord[i]);
						i++;
					}
					in_trie = trie.searchTrie(ranWord);
					if (in_trie == false) {
						cout << ranWord << " " << "is not in the dictionary" << endl;
					}

				}
				inFile1.close();
			}
		}

		// Adds a new words to the trie
		else if (input == 3) {
			string in = option3();
			trie.addtoTrie(in);
			cout << in << " Added"<< endl;
		}

		//saves the dictionary current state
		else if (input == 4) {
			bool result = option4();
			if (result == true) {
				cout << "Save Complete!" << endl;
			}
			else
			{
				cout << "Save Failed!" << endl;
			}
		}

		//takes user input and users input length to do a word compare with all words in the dictionary
		//prints out all words with the prefix which is the user input.
		else if (input == 5) {
			string inpu = option5();
			cout << inpu;
			string word1;
			ifstream inFile3;
			inFile3.open("dictionary.txt");
			while (getline(inFile3, word1))
			{
				if (word1.compare(0, inpu.length(), inpu) == 0) // start from index 0, compare the same number of characters as the length of the input, and the input
				{
					cout << word1 << endl;
				}
			}
			inFile3.close();
		}

		// additional feature
		// Addition and transposition
		// check if inputted word is in the dictionary
		// if no, Checks addition. done by removing one char at a time then searching the whole word til its valid. E.G. Hellxo > ellxo > Hllxo >Helxo > Hello. since it is an actual word it will stop.
		// if still no, check transposition. move letters around with adjacent char and search until valid .  E.G. hlep > lhep > help* since its an actual word it will stop.
		else if (input == 6) {
			string in = option6();
			int num = 0;
			bool in_trie = false;

			bool checkError = trie.searchTrie(in);

			if (checkError == false) {
				int option;
				//cout << "Check Addition(1) or Transposition(2) ? :";
				//cin >> option;
				//if (option == 1)
				//{
					while (num < in.length())
					{
						string checker = in;
						char tester = checker[num];
						string result = checker.erase(num, 1);
						in_trie = trie.searchTrie(result);
						if (in_trie == true) {
							cout << "(Addition) Did you mean " << result << endl;
							cout << "You added an extra " << tester << endl;
							checkError = true;
						}
						num++;
					}
				//}
				//else if (option == 2) {
					in_trie = false;
					num = 0;
					while (num < in.length() - 1)
					{
						string checkTrans = in;
						char holder = checkTrans[num];
						checkTrans[num] = checkTrans[num + 1];
						checkTrans[num + 1] = holder;
						in_trie = trie.searchTrie(checkTrans);
						if (in_trie == true) {
							cout << "(Transposition) Did you mean " << checkTrans << endl;
						}
						num++;
					}
				//}
				//else {
					//cout << " Not valid option" << endl;
				//}
				
			}
			else
			{
				cout << "Word is in Dictionary." << endl;
			}
			
		}

		// stops loop if 0 is inputted.
		else if (input == 0) {
			loopCon = false;
		}
		else
		{
			cout << "Invalid input! Try again." << endl;
		}
	}


	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
