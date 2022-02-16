#include "StudentIDlist.h"
using namespace std;

void StudentIDList::setHead(StudentIDNode* head) {
	Phead = head;
}

StudentIDNode* StudentIDList::getHead()const {
	return Phead;
}

// insertion sort
bool StudentIDList::sort() {
	StudentIDNode* pre = Phead->Pfront;
	if (!pre) {
		return 1;
	}
	StudentIDNode* cur = pre->Pfront;
	StudentIDNode* cmp;
	StudentIDNode* preCmp;
	StudentIDNode* insert;

	while (cur) {
		insert = cur;
		cur = cur->Pfront;
		cmp = Phead->Pfront;
		preCmp = Phead;
		while (cmp != insert) {
			if (strcmp(cmp->studentid, insert->studentid) > 0) {
				preCmp->Pfront = insert;
				insert->Pfront = cmp;
				break;
			}
			cmp = cmp->Pfront;
			preCmp = preCmp->Pfront;
		}
		if (pre->Pfront != cur)
			pre = pre->Pfront;
	}
	return 0;
}

// if studentID is already exist, return 1
bool StudentIDList::check(char studentID[]) {
	StudentIDNode* check = Phead->Pfront;
	while (check) {
		if (!strcmp(check->studentid, studentID)) {
			return 1;
		}
		check = check->Pfront;
	}
	return 0;
}