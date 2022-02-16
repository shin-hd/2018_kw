#include "Gradelist.h"

GradeList::GradeList() :Phead(NULL) {};
GradeList::~GradeList() {
	delete Phead;
}
void GradeList::setHead(GradeNode* head) {
	Phead = head;
}

GradeNode* GradeList::getHead()const {
	return Phead;
}