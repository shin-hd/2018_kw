#include <iostream>
#include <fstream>
#include <string>
#include "2D_linkedList.h"


int main() {
	ifstream input;
	input.open("input.txt");
	if (!input) {
		cout << "File doesn't be opened" << endl;
		return 1;
	}
	
	string word;
	LinkedList  linkedList;

	while(!input.eof()) { 
		getline(input, word);
		if (word == "")
			continue; // if word is empty, continue 
		linkedList.insertWord(word);
	}

	linkedList.sort(); // sorting
	
	cout << linkedList << endl;
	
	input.close();
	return 0;
}