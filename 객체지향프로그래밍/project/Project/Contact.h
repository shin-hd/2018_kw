#pragma once
#include <iostream>

// ��ȣ ����� ������ ������ Class
class ContactNode {
public:
	char contact[32];
	ContactNode *Pright;

	ContactNode();
	virtual ~ContactNode();
};