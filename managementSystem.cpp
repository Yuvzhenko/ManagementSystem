#include "managementSystem.h"

int ManagementSys::createAccountNumber() {
	fstream file("data.dat", ios::binary | ios::in);
	if (!file) {
		return 1;
	}
	file.seekg(0, ios::end);
	streampos fileSize = file.tellg();

	if (fileSize == 0) {
		file.close();
		return 1;
	}

	file.seekg(-static_cast<int>(sizeof(ManagementSys)), ios::end);

	ManagementSys temp;

	file.read(reinterpret_cast<char*>(&temp), sizeof(ManagementSys));
	file.close();

	if (!file) return 1;

	return temp.accNo + 1;
}

void ManagementSys::createAccount() {

	accNo = createAccountNumber();

	while (true) {
		cout << "Enter your name: ";
		cin >> ws; // clear spaces
		cin.getline(name, sizeof(name));
		if (strlen(name) < 2 || !isalpha(name[0])) {
			cout << "Invalid name. Please enter at least 2 letters.\n";
		}
		else break;
	}

	while (true) {
		cout << "Enter your Father name: ";
		cin.getline(Fname, sizeof(Fname));
		if (strlen(Fname) < 2 || !isalpha(Fname[0])) {
			cout << "Invalid name. Please enter at least 2 letters.\n";
		}
		else break;
	}

	while (true) {
		cout << "Enter your ID: ";
		cin.getline(ID, sizeof(ID));
		bool valid = true;
		for (int i = 0; ID[i]; i++) {
			if (!isdigit(ID[i])) valid = false;
		}
		if (!valid || strlen(ID) < 6) {
			cout << "Invalid ID. Use only digits and at least 6 characters.\n";
		}
		else break;
	}

	while (true) {
		cout << "Enter your Phone number (+90123456789): ";
		cin.getline(P_no, sizeof(P_no));
		bool valid = true;
		for (int i = 0; P_no[i]; i++) {
			if (!isdigit(P_no[i]) && P_no[i] != '+') valid = false;
		}
		if (!valid || strlen(P_no) < 7) {
			cout << "Invalid phone number.\n";
		}
		else break;
	}

	while (true) {
		cout << "Enter your email: ";
		cin.getline(email, sizeof(email));
		string em(email);
		if (em.find('@') == string::npos || em.find('.') == string::npos) {
			cout << "Invalid email format (something@something.sth).\n";
		}
		else break;
	}
	while (true) {
		cout << "Enter your amount :: ";
		cin >> amount;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "You entered incorrect amount... try again\n";
			continue;
		}
		// extra symbols checking
		char extra;
		if (cin.peek() != '\n') {
			cin >> extra;
			if (!isspace(extra)) {
				cin.ignore(32767, '\n');
				cout << "You entered incorrect amount... try again\n";
				continue;
			}
		}
		break;
	}
	cout << "This is your account number " << accNo << " please save it\n";

	fstream file("data.dat", ios::binary | ios::app);
	if (!file) {
		cout << "File opening error!" << endl;
		return;
	}
	file.write(reinterpret_cast<char*>(this), sizeof(ManagementSys));
	file.close();
}

void ManagementSys::searchAccount() {
	int search;
	cout << "Enter Account Number :: ";
	cin >> search;

	fstream file("data.dat", ios::binary | ios::in);
	if (!file) {
		cout << "File opening error!" << endl;
		return;
	}

	bool found = false;

	ManagementSys temp;

	while(file.read(reinterpret_cast<char*>(&temp), sizeof(ManagementSys)))
		if (temp.accNo == search) {
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
	fstream file("data.dat", ios::in | ios::out | ios::binary);
	if (!file) {
		cout << "File opening error!" << endl;
		return;
	}

	int searchAcc;
	cout << "Enter Account Number :: ";
	cin >> searchAcc;

	bool found = false;
	ManagementSys temp;

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
				tryAgain:
				cout << "Enter witch you would like to withdraw :: ";
				cin >> changeAmount;
				if (temp.amount - changeAmount < 0) {
					cout << "Your account does not have enough money\n";
					goto tryAgain;
				}
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

	fstream file("data.dat", ios::binary | ios::in);
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
	ManagementSys temp;

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
