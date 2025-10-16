#include "managementSystem.h"

using namespace std;
 
int main() {
	ManagementSys obj;
	while (true) {
		cout << "\n---------BANKING MANAGEMENT SYSTEM---------\n";
		cout << "1.Create new account\n";
		cout << "2.Search my account\n";
		cout << "3.Deposit money\n";
		cout << "4.Withdraw money\n";
		cout << "5.Delete my account\n";
		cout << "6.Exit\n";
		cout << "---------------------------------------------\n";
		cout << "Enter your choice :: ";
		char choice;
		cin >> choice;
		switch (choice) {
		case '1': {
			cin.ignore();
			obj.createAccount();
			continue;
		}
		case '2':
			cin.ignore();
			obj.searchAccount();
			continue;
		case '3':
			cin.ignore();
			obj.updateAmount(false);
			continue;
		case '4':
			cin.ignore();
			obj.updateAmount(true);
			continue;
		case '5':
			cin.ignore();
			obj.deleteAccount();
			continue;
		case '6':
			return 1;
		default:
			cout << "Incorrect input... try again\n";
			continue;
		}
	}

}