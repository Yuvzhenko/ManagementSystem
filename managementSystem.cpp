#include "managementSystem.h"

int ManagementSys::createAccountNumber() {
	file.open("data.dat", ios::in);
	if (!file) {
		cout << "File opening error!" << endl;
		return -1;
	}
	file.seekg(0, ios::end);
	streampos fileSize = file.tellg();

	if (fileSize == 0) {
		file.close();
		return 1;
	}

	file.seekg(-static_cast<int>(sizeof(ManagementSys)), ios::end);

	ManagementSys temp(false);

	file.read(reinterpret_cast<char*>(&temp), sizeof(ManagementSys));
	file.close();

	if (!file) return 1;

	return temp.accNo + 1;
}

void ManagementSys::searchAccount() {
	int search;
	cout << "Enter Account Number :: ";
	cin >> search;

	file.open("data.dat", ios::binary | ios::in);
	if (!file) {
		cout << "File opening error!" << endl;
		return;
	}

	bool found = false;

	ManagementSys temp(false);

	while(file.read(reinterpret_cast<char*>(&temp), sizeof(ManagementSys)))
		if (temp.accNo = search) {
			found = true;
			cout << "\n Account found:\n"
				 << "AccNo: " << temp.accNo << "\n"
				 << "Name: " << temp.name << "\n"
				 << "CNIC: " << temp.Fname << "\n"
				 << "Phone: " << temp.P_no << "\n"
				 << "Email: " << temp.email << "\n"
				 << "Amount: " << temp.amount << endl;
		}

	if (!found)
		cout << "\nAccount wasn't found!\n";

	file.close();
}

void ManagementSys::updateAmount(bool withdraw) {
	file.open("data.dat", ios::in | ios::out | ios::binary);
	if (!file) {
		cout << "File opening error!" << endl;
		return;
	}

	int searchAcc;
	cout << "Enter Account Number :: ";
	cin >> searchAcc;

	bool found = false;
	ManagementSys temp(false);

	while (file.read(reinterpret_cast<char*>(&temp), sizeof(ManagementSys))) {
		if (temp.accNo == searchAcc) {
			cout << "current amount :: " << temp.amount << endl;
			int changeAmount;

			if (!withdraw) {
				cout << "Enter witch you would like to add :: ";
				cin >> changeAmount;
				temp.amount += changeAmount;
			}
			else {
				cout << "Enter witch you would like to withdraw :: ";
				cin >> changeAmount;
				temp.amount -= changeAmount;
			}

			file.seekg(-static_cast<int>(sizeof(ManagementSys)), ios::cur);
			file.write(reinterpret_cast<char*>(&temp), sizeof(ManagementSys));
			cout << "Your new amount :: " << temp.amount << endl;

			found = true;
			break;
		}
	}
	if (!found) cout << "\nAccount not found\n";
	file.close();
}

void ManagementSys::deleteAccount() {
	int search;
	cout << "Enter Account Number :: ";
	cin >> search;

	file.open("data.dat", ios::binary | ios::in);
	if (!file) {
		cout << "File opening error!" << endl;
		return;
	}

	fstream tempFile("temp.dat", ios::binary | ios::out);
	if(!tempFile){
		cout << "File opening error!" << endl;
		file.close();
		return;
	}

	bool found = false;
	ManagementSys temp(false);

	while (file.read(reinterpret_cast<char*>(&temp), sizeof(ManagementSys))) {
		if (search == temp.accNo) {
			found = true;
			continue;
		}
		tempFile.write(reinterpret_cast<char*>(&temp), sizeof(ManagementSys));
	}
	file.close();
	tempFile.close();

	if (found) {
		remove("data.dat");
		rename("temp.dat", "data.dat");
	}
	else {
		remove("temp.dat");
		cout << "Account not found\n";
	}
}
