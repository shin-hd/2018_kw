#include "Manager.h"
using namespace std;

void Manager::READ_COMMAND(){
	ifstream cmdFile("Command.txt");
	ofstream log("LOG.txt");
	if (!cmdFile || !log) {
		cerr << "Error opening save file \n";
		return;
	}
	
	string cmdline, temp;
	char cmd[32], parameter[32], parameter2[32];
	int i, split, strinit;
	
	while (cmdFile.peek() != EOF) {
		getline(cmdFile, cmdline);

		i = -1;
		split = 0;
		strinit = 0;
		cmd[0] = NULL;
		parameter[0] = NULL;
		parameter2[0] = NULL;

		do {
			i++;
			if (cmdline[i] == ' ') {
				if (!split) {
					cmd[i] = '\0';
				}
				else {
					parameter[i - strinit] = '\0';
				}
				split++;
				strinit = i + 1;
			} // split setting
			else if (!split) {
				cmd[i] = cmdline[i];
			} // get cmd
			else if(split == 1){
				parameter[i - strinit] = cmdline[i];
			} // get parameter
			else {
				parameter2[i - strinit] = cmdline[i];
			} // get parameter2
		} while (cmdline[i] != '\0');
		
		if (parameter2[0] != '\0') {
			cout << "[" << cmd << " " << parameter << " " << parameter2 << "]\n";
			log << "[" << cmd << " " << parameter << " " << parameter2 << "]\n";
		}
		else if (parameter[0] != '\0') {
			cout << "[" << cmd << " " << parameter << "]\n";
			log << "[" << cmd << " " << parameter << "]\n";
		}
		else {
			cout << "[" << cmd << "]\n";
			log << "[" << cmd << "]\n";
		}

		if (!strcmp(cmd, "LOAD")) {
			try {
				LOAD();
				cout << "Success\n\n";
				log << "Success\n\n";
			}
			catch (...) {
				cout << "Error_code: 100\n\n";
				log << "Error_code: 100\n\n";
			}
		}
		else if (!strcmp(cmd, "ADD")) {
			try {
				ADD();
				cout << "Success\n\n";
				log << "Success\n\n";
			}
			catch (char c) {
				if (c == '0') {
					cout << "Error code: 200\n\n";
					log << "Error code: 200\n\n";
				}
				else {
					cout << "Error code: 200-" << c << "\n\n";
					log << "Error code: 200-" << c << "\n\n";
				}
			}
		}
		else if (!strcmp(cmd, "UPDATE")) {
			try {
				UPDATE();
				cout << "Success\n\n";
				log << "Success\n\n";
			}
			catch (char c) {
				if (c == '0') {
					cout << "Error code: 300\n\n";
					log << "Error code: 300\n\n";
				}
				else {
					cout << "Error code: 300-" << c << "\n\n";
					log << "Error code: 300-" << c << "\n\n";
				}
			}
		}
		else if (!strcmp(cmd, "MODIFY_DEPARTMENT")) {
			try {
				MODIFY_DEPARTMENT(parameter, parameter2);
				cout << "Success\n\n";
				log << "Success\n\n";
			}
			catch (...) {
				cout << "Error code: 400\n\n";
				log << "Error code: 400\n\n";
			}
		}
		else if (!strcmp(cmd, "DELETE_DEPARTMENT")) {
			try {
				DELETE_DEPARTMENT(parameter);
				cout << "Success\n\n";
				log << "Success\n\n";
			}
			catch (...) {
				cout << "Error code: 500\n\n";
				log << "Error code: 500\n\n";
			}
		}
		else if (!strcmp(cmd, "PRINT")) {
			try {
				log.close();
				if (parameter[0] == '\0') {
					PRINT();
				}
				else {
					PRINT(parameter);
				}
				log.open("LOG.txt", ios::app);
			}
			catch (char c) {
				cout << "Error code: 600" << c << "\n\n";
				log << "Error code: 600" << c << "\n\n";
			}
		}
		else if (!strcmp(cmd, "PRINT_SUTDENT_ID")) { /// student
			try {
				log.close();
				//PRINT_STUDENT_ID();
				log.open("LOG.txt", ios::app);
			}
			catch (...) {
				cout << "Error code: 700\n\n";
				log << "Error code: 700\n\n";
			}
		}
		else if (!strcmp(cmd, "PRINT_CONTACT")) {
			try {				
				log.close();
				//PRINT_CONTACT();
				log.open("LOG.txt", ios::app);
			}
			catch (...) {
				cout << "Error code: 800\n\n";
				log << "Error code: 800\n\n";
			}
		}
		else if (!strcmp(cmd, "FIND_NAME")) {
			try {
				log.close();
				//FIND_NAME(parameter);
				log.open("LOG.txt", ios::app);
			}
			catch (...) {
				cout << "Error code: 900\n\n";
				log << "Error code: 900\n\n";
			}
		}
		else if (!strcmp(cmd, "SAVE")) {
			if (parameter[0] == '\0') {
				cout << "Error code: 1000\n\n";
				log << "Error code: 1000\n\n";
				continue;
			}
			SAVE(parameter);
			cout << cmd << " Success\n\n";
			log << cmd << " Success\n\n";
		}
		else if (!strcmp(cmd, "EXIT")) {
			cmdFile.close();
			log.close();
			return;
		}
		else {
			cout << "Error code: 000\n\n";
			log << "Error code: 000\n\n";
		}
	}
}

bool Manager::LOAD() {
	ifstream infoFile("Information.txt");
	if (!infoFile) {
		throw;
	}
	string infoline;
	char dep[32], name[32], studentID[32], contact[32];
	int grade, i, j, split, strinit;

	while (infoFile.peek() != EOF) {
		getline(infoFile, infoline);
		
		i = -1;
		j = 0;
		split = 0;
		strinit = 0;
		dep[0] = NULL;
		name[0] = NULL;
		studentID[0] = NULL;
		contact[0] = NULL;

		do {
			i++;
			if (infoline[i] == '\t') {
				switch (split) {
				case 0:
					dep[j] = '\0';
					break;
				case 1:
					name[j] = '\0';
					break;
				case 3:
					studentID[j] = '\0';
					break;
				}
				split++;
				j = -1;
			} // split setting
			else if (!split) {
				dep[j] = infoline[i];
			} // get department
			else if (split == 1) {
				name[j] = infoline[i];
			} // get name
			else if (split == 2) {
				grade = (int)(infoline[i]-'0');
			} // get grade
			else if (split == 3) {
				studentID[j] = infoline[i];
			}
			else {
				contact[j] = infoline[i];
			}
			j++;
		} while (infoline[i] != '\0');

		departmentlist.insert(dep);
		// namelist.insert returns namenode*
		departmentlist.insertStudent(namelist.insert(name, grade, studentID, contact), dep);
	}

	// set IDlist, contctlist, gradelist
	namelist.setSublist();
	IDlist.setHead(namelist.getIDhead());
	contctlist.setHead(namelist.getChead());
	gradelist.setHead(namelist.getGhead());

	departmentlist.sort();

	infoFile.close();
	return 0;
}

bool Manager::ADD() {
	ifstream infoFile("Add_information.txt");
	if (!infoFile) {
		throw '0';
	}
	string infoline;
	char dep[32], name[32], studentID[32], contact[32];
	int grade, i, j, split, strinit;
	int error = 0;

	while (infoFile.peek() != EOF) {
		getline(infoFile, infoline);

		i = -1;
		j = 0;
		split = 0;
		strinit = 0;
		dep[0] = NULL;
		name[0] = NULL;
		studentID[0] = NULL;
		contact[0] = NULL;

		do {
			i++;
			if (infoline[i] == '\t') {
				switch (split) {
				case 0:
					dep[j] = '\0';
					break;
				case 1:
					name[j] = '\0';
					break;
				case 3:
					studentID[j] = '\0';
					break;
				}
				split++;
				j = -1;
			} // split setting
			else if (!split) {
				dep[j] = infoline[i];
			} // get department
			else if (split == 1) {
				name[j] = infoline[i];
			} // get name
			else if (split == 2) {
				grade = (int)(infoline[i] - '0');
			} // get grade
			else if (split == 3) {
				studentID[j] = infoline[i];
			}
			else {
				contact[j] = infoline[i];
			}
			j++;
		} while (infoline[i] != '\0');
		if (IDlist.check(studentID) || contctlist.check(contact)) {
			error = 1;
			continue;
		}
		departmentlist.insert(dep);
		// namelist.insert returns namenode
		departmentlist.insertStudent(namelist.insert(name, grade, studentID, contact), dep);
	}

	infoFile.close();
	if (error)
		throw '1';
	return 0;
}

bool Manager::UPDATE() {
	ifstream update("Update_information.txt");
	if (!update) {
		throw '0';
	}
	string updateline;

	char dep[32], name[32], studentID[32], contact[32];
	int grade, i, j, split, strinit;

	while (update.peek() != EOF) {
		getline(update, updateline);

		i = -1;
		j = 0;
		split = 0;
		strinit = 0;
		dep[0] = NULL;
		name[0] = NULL;
		studentID[0] = NULL;
		contact[0] = NULL;

		do {
			i++;
			if (updateline[i] == '\t') {
				switch (split) {
				case 0:
					dep[j] = '\0';
					break;
				case 1:
					name[j] = '\0';
					break;
				case 3:
					studentID[j] = '\0';
					break;
				}
				split++;
				j = -1;
			} // split setting
			else if (!split) {
				dep[j] = updateline[i];
			} // get department
			else if (split == 1) {
				name[j] = updateline[i];
			} // get name
			else if (split == 2) {
				grade = (int)(updateline[i] - '0');
			} // get grade
			else if (split == 3) {
				studentID[j] = updateline[i];
			}
			else {
				contact[j] = updateline[i];
			}
			j++;
		} while (updateline[i] != '\0');

		//update
		departmentlist.changeDep(departmentlist.getDep(name), dep, name, grade, studentID, contact);
	}

	update.close();
	return 0;
}

bool Manager::MODIFY_DEPARTMENT(char before[], char after[]) {
	departmentlist.modify_department(before, after);
	return 0;
}

bool Manager::DELETE_DEPARTMENT(char department[]) {
//	departmentlist.pop(department);
	namelist.setSublist();
	return 0;
}

void Manager::PRINT() {
	departmentlist.nameSort_Descend();
	departmentlist.print(); // descending
}

void Manager::PRINT(char department[]) {
	departmentlist.nameSort_Descend();
	departmentlist.print(department); // descending
}

void Manager::PRINT_STUDENT_ID() {
	IDlist.sort();
	namelist.printID(); // insert, ascending
}

void Manager::PRINT_CONTACT() {
	contctlist.sort();
	namelist.printContct(); // select, descending
}

void Manager::FIND_NAME(char name[]) {
	namelist.sort();
	namelist.get(name); // bubble, ascending
}

bool Manager::SAVE(char fileName[]) {
	departmentlist.sort_Ascend();
	departmentlist.nameSort_Ascend(); // sorting
	departmentlist.save(fileName);
	return 0;
}