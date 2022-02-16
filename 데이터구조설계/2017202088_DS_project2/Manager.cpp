#include "Manager.h"
#include<sstream>

Manager::Manager(int bpOrder) {
	fout.open("log.txt", ios::app);
	avl = new AVLTree(&fout);
	bp = new BpTree(&fout, bpOrder);
}

Manager::~Manager() {
	delete avl;
	delete bp;
	fout.close();
}

void Manager::run(const char *command_txt) {
	ifstream fin;
	fin.open(command_txt);
	istringstream commandStream;
	int load = -1;

	if (!fin) {
		cout << "[ERROR] command file open error!" << endl;
		return;
	}

	char str[30] = { 0 };
	char str2[30] = { 0 };
	char buf[128] = { 0 };
	
	while (fin.getline(buf, 64)) {
		commandStream.clear();
		commandStream.str(buf);
		commandStream >> str;

		if (strcmp(str, "LOAD") == 0) {
			if (load == 1) {
				printErrorCode(100);
			}
			else if (commandStream >> str || !LOAD()) {
				printErrorCode(100);
			}
			else {
				fout << "======== LOAD ========" << endl;
				fout << "Success" << endl;
				fout << "=======================" << endl;
			}
			load = 1;
		}
		else if (strcmp(str, "SEARCH_AVL") == 0) {
			if (commandStream >> str) {
				if(!SEARCH_AVL(str))
					printErrorCode(300);
			}
			else
				printErrorCode(300);
		}
		else if (strcmp(str, "SEARCH_BP") == 0) {
			if (commandStream >> str && commandStream >> str2) {
				if(!SEARCH_BP(atof(str), atof(str2)))
					printErrorCode(200);
			}
			else
				printErrorCode(200);
		}
		else if (strcmp(str, "RANK") == 0) {
			if (!RANK())
				printErrorCode(400);
		}
		else if (strcmp(str, "PRINT_AVL") == 0) {
			if(!PRINT_AVL())
				printErrorCode(600);
		}
		else if (strcmp(str, "PRINT_BP") == 0) {
			if(!PRINT_BP())
				printErrorCode(500);
		}
		else if (strcmp(str, "EXIT") == 0) {
			fout << "======== EXIT ========" << endl;
			fout << "Success" << endl;
			fout << "=======================" << endl;
			break;
		}
		fout << endl;
	}
	fin.close();
}

bool Manager::LOAD() {
	char str[30] = { 0 };
	char buf[128] = { 0 };
	
	ifstream fin;
	fin.open("stock_list.txt");
	istringstream loadStream;

	if (!fin) { // ifstream error
		return false;
	}

	while (fin.getline(buf, 64)) {
		StockData *pSto;
		loadStream.clear();
		loadStream.str(buf);

		// read StockData
		pSto = new StockData();

		loadStream >> str;
		pSto->setStockID(atoi(str));
		loadStream >> str;
		pSto->setName(str);
		loadStream >> str;
		int open = atoi(str);
		pSto->setOpening_Price(open);
		loadStream >> str;
		int close = atoi(str);
		pSto->setClosing_Price(close);
		loadStream >> str;
		int volume = atoi(str);
		pSto->setVolume(volume);

		pSto->setEarning(open, close);

		// insert StockData
		avl->Insert(pSto);
		bp->Insert(pSto);
	}
	return true;
}

bool Manager::SEARCH_AVL(char *name) {
	if (!avl->Search(name))
		return false;
	else
		return true;
}

bool Manager::SEARCH_BP(double a, double b) {
	if (!bp->Search(a, b))
		return false;
	else
		return true;
}

bool Manager::RANK() {
	if (!avl->Rank())
		return false;
	else
		return true;
}

bool Manager::PRINT_AVL() {
	if (!avl->Print())
		return false;
	else
		return true;
}

bool Manager::PRINT_BP() {
	if (!bp->Print())
		return false;
	else
		return true;
}

void Manager::printErrorCode(int n) {
	fout << "======== ERROR ========" << endl;
	fout << n << endl;
	fout << "=======================" << endl;
}
