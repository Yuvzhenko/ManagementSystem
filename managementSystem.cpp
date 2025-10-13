#include "managementSystem.h"

int ManagementSys::createAccountNumber() {
	file.open("data.txt", ios::in);
	if (!file) {
		cout << "File opening error!" << endl;
		return -1;
	}
	string line;
	while (getline(file, line));
	file.close();

	if (line.empty())
		line = "0";

	stringstream ss(line);
	ss >> accNo;
	return accNo++;

}

void ManagementSys::searchAccount() {
	int search;
	cout << "Enter Account Number :: ";
	cin >> search;

	file.open("data.txt", ios::in);
	if (!file) {
		cout << "File opening error!" << endl;
		return;
	}

	bool found = false;

	while(file >> accNo >> name >> Fname >> ID >> P_no >> email >> amount)
		if (accNo = search) {
			found = true;
			cout << "\n Account found:\n"
				 << "AccNo: " << accNo << "\n"
				 << "Name: " << name << "\n"
				 << "CNIC: " << Fname << "\n"
				 << "Phone: " << P_no << "\n"
				 << "Email: " << email << "\n"
				 << "Amount: " << amount << endl;
		}
	if (!found)
		cout << "\nAccount wasn't found!\n";

	file.close();
}
/*
void ManagementSys::updateAmount() {
	file.open("data.txt", ios::in | ios::out | ios::binary);
	if (!file) {
		cout << "File opening error!" << endl;
		return;
	}

	int searchAcc;
	cout << "Enter Account Number :: ";
	cin >> searchAcc;

	bool found = false;

	while (file.read(reinterpret_cast<char*>(this), sizeof(ManagementSys))) {
		if (accNo == searchAcc) {
			cout << ""
		}
	}
}
*/