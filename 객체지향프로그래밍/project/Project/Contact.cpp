#include "Contact.h"

ContactNode::ContactNode() :contact(""), Pright(NULL) {};
ContactNode::~ContactNode() {
	delete Pright;
}