#pragma once
#include <iostream>

// DepartmentNode와 NameNode가 상속하는 Class
class Node {
public:
	Node *Pnext;
	Node *Pprev;
	Node *Pup;
	Node *Pdown;

	Node() :Pnext(NULL), Pprev(NULL), Pup(NULL), Pdown(NULL) {}
	virtual ~Node() {}
};