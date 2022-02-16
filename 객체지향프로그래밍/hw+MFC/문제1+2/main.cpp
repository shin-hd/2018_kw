#include <iostream>
#include <string>

#include "LinkedList.h"

using namespace std;

int main()
{

	kw::LinkedList<int> linkedList;

	cout << "Initialization" << endl << endl;

	cout << "insertion (1)" << endl << endl;
	cout << "insertion (3)" << endl << endl;
	cout << "insertion (4)" << endl << endl;
	cout << "insertion (6)" << endl << endl;

	linkedList.insert(1);
	linkedList.insert(3);
	linkedList.insert(4);
	linkedList.insert(6);

	cout << "Size of linked list = " << linkedList.size() << endl;
	cout << linkedList << endl;

	cout << "After reverse function" << endl << endl;
	linkedList.reverse();
	cout << linkedList << endl;

	cout << "After sort function" << endl << endl;
	linkedList.sort();
	cout << linkedList << endl;

	cout << "Test insertion" << endl << endl;
	cout << "insertion (1, 2)" << endl << endl;
	cout << "insertion (4, 5)" << endl << endl;

	linkedList.insert(1, 2);
	linkedList.insert(4, 5);

	cout << "Size of linked list = " << linkedList.size() << endl;
	cout << linkedList << endl;

	cout << "Test pop" << endl << endl;
	cout << "pop (0)" << endl << endl;
	cout << "pop (3)" << endl << endl;
	cout << "pop ()" << endl << endl;

	linkedList.pop(0);
	linkedList.pop(3);
	linkedList.pop();

	cout << "Size of linked list = " << linkedList.size() << endl;
	cout << linkedList << endl;

	cout << "Test get and set function" << endl << endl;

	cout << "linkedList.get(1)  = " << linkedList.get(1) << endl;

	linkedList.set(1, 50);

	cout << "linkedList.set(1, 50)" << endl;
	cout << "linkedList.get(1)  = " << linkedList.get(1) << endl << endl;

	cout << "Test clear" << endl << endl;
	linkedList.clear();

	cout << "Size of linked list  = " << linkedList.size() << endl;
	cout << linkedList << endl;

	return 0;
}
