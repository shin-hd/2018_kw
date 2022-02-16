#pragma once
#include "Node.h"
#include "Contact.h"
#include "Grade.h"
#include "StudentID.h"

// �̸� ����� ������ ������ Class
// Node�� ��ӹ��� ��-�Ʒ� �ּҷ� department ����
// Node�� ��ӹ��� ��-�� �ּҷ� name ����
class NameNode :public Node {
public:
	char name[32];
	ContactNode *Pright;
	GradeNode *Pleft;
	StudentIDNode *Pfront;

	NameNode() :Node(), name(""), Pright(NULL), Pleft(NULL), Pfront(NULL) {}
	virtual ~NameNode() {}
};