#pragma once
#include <iostream>
#include <fstream>

#include <sstream>
#include <string>

using namespace std;

class ManagementSys {
	int accNo;
	char name[25];
	char Fname[25];
	char ID[25];
	char P_no[20];
	char email[30];
	double amount;

public:
	void createAccount();
	void searchAccount();
	void updateAmount(bool withdraw);
	void deleteAccount();

private:
	int createAccountNumber();
};