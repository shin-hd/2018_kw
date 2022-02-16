#include <iostream>
#include "Queue.h"
using namespace std;

int main() {
	Queue queue;
	int sel;

	queue.setSize();
	do {
		queue.printMenu();
		cout << "Select menu : ";
		cin >> sel;
		switch (sel) {
		case 1:
			queue.Push();
			break;
		case 2:
			queue.Pop();
			break;
		case 3:
			queue.showAll();
			break;
		case 4:
			break;
		default:
			cout << "Please select effective number" << endl;
			break;
		}
	} while (sel != 4);
	
	return 0;
}