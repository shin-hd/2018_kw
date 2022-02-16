#pragma once
#include <iostream>

// 번호 노드의 정보를 가지는 Class
class ContactNode {
public:
	char contact[32];
	ContactNode *Pright;

	ContactNode();
	virtual ~ContactNode();
};