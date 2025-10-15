#pragma once
#include <iostream>
#include <fstream>

#include <sstream>
#include <string>

using namespace std;

class ManagementSys {
	fstream file;
	int accNo;
	char name[25];
	char Fname[25];
	char ID[25];
	char P_no[20];
	char email[30];
	double amount;
public:
	ManagementSys(bool constructor = true) {
		if (constructor) {
			accNo = createAccountNumber();
			cout << "Enter your name :: ";
			cin >> name;
			cout << "Enter your Father name :: ";
			cin >> Fname;
			cout << "Enter your ID :: ";
			cin >> ID;
			cout << "Enter your Phone number :: ";
			cin >> P_no;
			cout << "Enter your email :: ";
			cin >> email;
			cout << "Enter your amount :: ";
			cin >> amount;
			cout << "This is your account number " << accNo << " please save it\n";

			file.open("data.dat", ios::binary | ios::app);
			if (!file) {
				cout << "File opening error!" << endl;
				return;
			}
			file.write(reinterpret_cast<char*>(this), sizeof(ManagementSys));
			file.close();
		}
	}

	void searchAccount();
	void updateAmount(bool withdraw);
	void deleteAccount();

private:
	int createAccountNumber();
};