#include "DepartmentList.h"
using namespace std;

bool DepartmentList::insert(char department[]) {
	DepartmentNode* newDep = new DepartmentNode;

	strcpy_s(newDep->de_name, department);
	newDep->Pnext = Phead;

	if (Phead == NULL) {
		Phead = newDep;
		newDep->Pnext = Phead; // befor Pnext was NULL, so reset Pnext
	}
	else {
		DepartmentNode* check = Phead;
		do {
			if (!strcmp(department, check->de_name)) {
				// same department is exist
				return 1;
			}
			check = (DepartmentNode*)check->Pnext;
		} while (check != Phead);
		Node* cur = Phead;
		while (cur->Pnext != Phead) {
			cur = cur->Pnext;
		}
		cur->Pnext = newDep;
	}

	return 0;
}

bool DepartmentList::pop(char department[]) {
	if (Phead == NULL) {
		return 0;
	}
	Node* cur = NULL;
	Node* pop = Phead;
	Node* prePop = NULL;

	do {
		if (!strcmp(((DepartmentNode*)pop)->de_name, department)) {
			if (!prePop) {
				while (prePop->Pnext != Phead) {
					prePop = prePop->Pnext;
				}
			} // set prePop
			prePop->Pnext = pop->Pnext;
			cur = pop->Pdown;
			while(cur) {
				if (!cur->Pnext) {
					cur = cur->Pdown;
					continue;
				}
				cur->Pnext = cur->Pprev->Pnext;
				cur->Pprev = cur->Pnext->Pprev;
				cur = cur->Pdown;
			} // new link
			cur = pop;
			do {
				pop = cur;
				cur = pop->Pdown;
				delete pop;
			} while (cur); // delete
			return 0;
		} // delete

		prePop = pop;
		pop = pop->Pnext;
	} while (pop != Phead);
	throw; // pop does not work
}

bool DepartmentList::modify_department(char before[], char after[]) {
	Node* cur = Phead;
	DepartmentNode* depCur = Phead;
	Node* beforeDep = NULL;
	Node* afterDep = NULL;

	do { // find a node that has same de_name as before and after
		if (!strcmp(depCur->de_name, before)) {
			beforeDep = depCur;
		}
		else if (!strcmp(depCur->de_name, after)) {
			afterDep = depCur;
		}
		depCur = (DepartmentNode*)depCur->Pnext;
	} while (depCur != Phead);

	if (!beforeDep) {
		throw;
	} // if before department is not exist
	else if (!afterDep) {
		strcpy_s(((DepartmentNode*)beforeDep)->de_name, after);
	} // if after department is not exist
	else {
		while (cur->Pnext != beforeDep) {
			cur = cur->Pnext;
		} // find pre_beforeDep
		cur->Pnext = beforeDep->Pnext; // cut links of beforDep

		while (afterDep->Pdown) {
			afterDep = afterDep->Pdown;
		} // find the afterName's tail
		afterDep->Pdown = beforeDep->Pdown;
		beforeDep->Pdown = NULL;
		delete beforeDep;
	} // if after department is already exist

	return 0;
}

bool DepartmentList::sort() {
	Node* cur = Phead->Pnext;
	Node* pre = Phead;
	if (cur == NULL) {
		return 1;
	} // Only one department is exist, do not sorting
	Node* cmp = NULL;
	Node* preCmp = NULL;
	DepartmentNode* insert;

	do {
		insert = (DepartmentNode*)cur;
		cmp = Phead;
//		if (cur->Pnext != Phead)
			cur = cur->Pnext; // move cur to next
		while (cmp != insert) {
			// insert's de_name is greater than cmp's de_name
			if (strcmp(((DepartmentNode*)cmp)->de_name, insert->de_name) < 0) {
				pre->Pnext = insert->Pnext;
				insert->Pnext = cmp; 
				if (cmp == Phead) {
					while (cmp->Pnext != Phead) {
						cmp = cmp->Pnext;
					}
					cmp->Pnext = insert;
					Phead = insert;
				} // if cmp is head, replace head to insert
				else
					preCmp->Pnext = insert; // cmp is not head
			break;
			}
			preCmp = cmp;
			cmp = cmp->Pnext;
		}
		// if insert was not relocated, move pre
		if (pre->Pnext != cur)
			pre = pre->Pnext;
	} while (cur != Phead);
	
	return 0;
}

bool DepartmentList::sort_Ascend() {
	Node* cur = Phead->Pnext;
	Node* pre = Phead;
	if (cur == NULL) {
		return 1;
	} // Only one department is exist, do not sorting
	Node* cmp = NULL;
	Node* preCmp = NULL;
	DepartmentNode* insert;

	do {
		insert = (DepartmentNode*)cur;
		cmp = Phead;
		//		if (cur->Pnext != Phead)
		cur = cur->Pnext; // move cur to next
		while (cmp != insert) {
			// insert's de_name is greater than cmp's de_name
			if (strcmp(((DepartmentNode*)cmp)->de_name, insert->de_name) > 0) {
				pre->Pnext = insert->Pnext;
				insert->Pnext = cmp;
				if (cmp == Phead) {
					while (cmp->Pnext != Phead) {
						cmp = cmp->Pnext;
					}
					cmp->Pnext = insert;
					Phead = insert;
				} // if cmp is head, replace head to insert
				else
					preCmp->Pnext = insert; // cmp is not head
				break;
			}
			preCmp = cmp;
			cmp = cmp->Pnext;
		}
		// if insert was not relocated, move pre
		if (pre->Pnext != cur)
			pre = pre->Pnext;
	} while (cur != Phead);

	return 0;
}

bool DepartmentList::insertStudent(NameNode* insert, char department[]) {
	Node* cur = Phead;
	Node* nameCur;
	DepartmentNode* depCur;

	do {
		depCur = (DepartmentNode*)cur;

		if (!strcmp(depCur->de_name, department)) {
			nameCur = cur;
			while (nameCur->Pdown) {
				nameCur = nameCur->Pdown;
			}
			nameCur->Pdown = insert;
			insert->Pup = nameCur;
			return 0;
		} // name insertion

		cur = cur->Pnext;
	} while (cur != Phead);

	return 1; // name insertion does not work
}

bool DepartmentList::nameSort_Ascend() {
	Node* depCur = Phead;
	if (depCur == NULL) {
		return 1;
	}
	Node* cur = NULL;
	Node* pre = NULL;
	Node* cmp = NULL;
	Node* preCmp = NULL;
	NameNode* insert = NULL;

	do {
		cur = depCur->Pdown;
		pre = depCur;
		while (cur) {
			if (!cur->Pdown)
				break;
			insert = (NameNode*)cur;
			preCmp = depCur;
			cmp = depCur->Pdown;
			cur = cur->Pdown; // move cur to next
			while (cmp != insert) {
				if (strcmp(((NameNode*)cmp)->name, insert->name) > 0) {
					pre->Pdown = insert->Pdown;
					if (pre->Pdown)
						pre->Pdown->Pup = pre; // isolating insert

					insert->Pdown = cmp;
					cmp->Pup = insert;
					preCmp->Pdown = insert;
					insert->Pup = preCmp;
					break;
				}
				preCmp = cmp;
				cmp = cmp->Pdown;
			}
			// if insert was not relocated, move pre
			if (pre->Pdown != cur)
				pre = pre->Pdown;
		} // name loop
		depCur = depCur->Pnext;
	} while (depCur != Phead); // department loop
	return 0;
}

bool DepartmentList::nameSort_Descend() {
	Node* depCur = Phead;
	if (depCur == NULL) {
		return 1;
	}
	Node* cur = NULL;
	Node* pre = NULL;
	Node* cmp = NULL;
	Node* preCmp = NULL;
	NameNode* insert = NULL;

	do {
		cur = depCur->Pdown;
		pre = depCur;
		while(cur) {
			if (!cur->Pdown)
				break;
			insert = (NameNode*)cur;
			preCmp = depCur;
			cmp = depCur->Pdown;
			cur = cur->Pdown; // move cur to next
			while (cmp != insert) {
				// insert's name is greater than cmp's name
				if (strcmp(((NameNode*)cmp)->name, insert->name) < 0) {
					pre->Pdown = insert->Pdown;
					if (pre->Pdown)
						pre->Pdown->Pup = pre; // isolating insert

					insert->Pdown = cmp;
					cmp->Pup = insert;
					preCmp->Pdown = insert;
					insert->Pup = preCmp;
					break;
				}
				preCmp = cmp;
				cmp = cmp->Pdown;
			}
			// if insert was not relocated, move pre
			if (pre->Pdown != cur)
				pre = pre->Pdown;
		} // name loop
		depCur = depCur->Pnext;
	} while (depCur != Phead); // department loop
	return 0;
}

void DepartmentList::print() {
	DepartmentNode* dep = (DepartmentNode*)Phead;
	if (!dep)
		throw '1';
	NameNode* name;
	GradeNode* gradeNode;
	StudentIDNode* ID;
	ContactNode* contct;
	string print("");
	char grade[2];
	grade[1] = '\0';

	do {
		dep = (DepartmentNode*)dep->Pnext;
		name = (NameNode*)dep->Pdown;
		while (name) {
			gradeNode = name->Pleft;
			ID = name->Pfront;
			contct = name->Pright;

			print.append(dep->de_name);
			print.append("/");
			print.append(name->name);
			print.append("/");
			grade[0] = gradeNode->grade + '0';
			print.append(grade);
			print.append("/");
			print.append(ID->studentid);
			print.append("/");
			print.append(contct->contact);
			print.append("\n");

			name = (NameNode*)name->Pdown;
		}
	} while (dep->Pnext != Phead);
	cout << print << endl << endl;
	ofstream log("LOG.txt", ios::app);
	log << print << endl << endl;
	log.close();
}

void DepartmentList::print(char department[]) {
	DepartmentNode* dep = (DepartmentNode*)Phead;
	if (!dep)
		throw '1';
	NameNode* name;
	GradeNode* gradeNode;
	StudentIDNode* ID;
	ContactNode* contct;

	while (strcmp(department, dep->de_name)) {
		dep = (DepartmentNode*)dep->Pnext;
		if (dep == Phead)
			throw '2'; // Does not exist departmentNode
	}
	
	string print("");
	name = (NameNode*)dep->Pdown;
	char grade[2];
	grade[1] = '\0';

	while (name) {
		gradeNode = name->Pleft;
		ID = name->Pfront;
		contct = name->Pright;

		print.append(dep->de_name);
		print.append("/");
		print.append(name->name);
		print.append("/");
		grade[0] = gradeNode->grade + '0';
		print.append(grade);
		print.append("/");
		print.append(ID->studentid);
		print.append("/");
		print.append(contct->contact);
		print.append("\n");

		name = (NameNode*)name->Pdown;
	}
	cout << print << endl << endl;
	ofstream log("LOG.txt", ios::app);
	log << print << endl << endl;
	log.close();
}

bool DepartmentList::save(char fileName[]) {
	ofstream saveFile(fileName); // 과순으로 오름차순, 학과기준->이름
	if (!saveFile) {
		cerr << "Error opening save file \n";
		return 1;
	}
	DepartmentNode* dep = (DepartmentNode*)Phead->Pnext;
	NameNode* name;
	GradeNode* gradeNode;
	StudentIDNode* ID;
	ContactNode* contct;
	string print("");
	char grade[2];
	grade[1] = '\0';

	while (dep != Phead) {
		name = (NameNode*)dep->Pdown;
		while (name) {
			gradeNode = name->Pleft;
			ID = name->Pfront;
			contct = name->Pright;

			print.append(dep->de_name);
			print.append("/");
			print.append(name->name);
			print.append("/");
			grade[0] = gradeNode->grade + '0';
			print.append(grade);
			print.append("/");
			print.append(ID->studentid);
			print.append("/");
			print.append(contct->contact);
			print.append("\n");

			name = (NameNode*)name->Pdown;
		}
		dep = (DepartmentNode*)dep->Pnext;
	}
	saveFile << print << endl;
	saveFile.close();
	return 0;
}

bool DepartmentList::changeDep(char before[], char after[], char name[], int grade, char studentID[], char contact[]) {
	Node* nameNode = Phead->Pnext;
	Node* cur = Phead->Pnext;
	NameNode* temp;

	// finde nameNode that has same name
	while (nameNode) {
		if (strcmp(((DepartmentNode*)nameNode)->de_name, before)) {
			nameNode = nameNode->Pdown;
			while (strcmp(((NameNode*)nameNode)->name, name)) {
				nameNode = nameNode->Pdown;
				if (!nameNode) {
					//error: cannot find name in before
					return 1;
				}
			} // findout

			// delete link
			nameNode->Pup->Pdown = nameNode->Pdown;
			nameNode->Pdown->Pup = nameNode->Pup;
			// reset grade, ID, contact
			temp = (NameNode*)nameNode;
			temp->Pleft->grade = grade;
			
			if (!strcmp(temp->Pfront->studentid, studentID) || !strcmp(temp->Pright->contact, contact))
				throw '1'; // same ID or contact

			strcpy_s(temp->Pfront->studentid, studentID);
			strcpy_s(temp->Pright->contact, contact);
			break;
		}
		nameNode = nameNode->Pnext;
	}
	
	// insert nameNode in new department
	while (cur) {
		if (strcmp(((DepartmentNode*)cur)->de_name, after)) {
			nameNode->Pdown = cur->Pdown;
			cur->Pdown = nameNode;
			return 0;
		}
		cur = cur->Pnext;
	}

	return 1; // insertion error
}

char* DepartmentList::getDep(char name[]) {
	Node* dep = Phead;
	NameNode* cur = NULL;
	do {
		cur = (NameNode*)dep->Pdown;
		while (cur) {
			if (!strcmp(cur->name, name)) {
				return ((DepartmentNode*)dep)->de_name;
			}
			cur = (NameNode*)cur->Pdown;
		}
		dep = dep->Pnext;
	} while (dep != Phead);
	throw '2'; // name is not exist
}