#pragma once
#include <iostream>

// �й� ����� ������ ������ Class
class StudentIDNode {
public:
	char studentid[32];
	StudentIDNode *Pfront;

	StudentIDNode();
	virtual ~StudentIDNode();
};