#pragma once
#include <iostream>

// DepartmentNode�� NameNode�� ����ϴ� Class
class Node {
public:
	Node *Pnext;
	Node *Pprev;
	Node *Pup;
	Node *Pdown;

	Node() :Pnext(NULL), Pprev(NULL), Pup(NULL), Pdown(NULL) {}
	virtual ~Node() {}
};