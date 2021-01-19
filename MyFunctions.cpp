/*
 * MyFunctions.cpp
 *
 *  Created on: Jan 14, 2021
 *      Author: khang.le
 */
#include "MyFunctions.h"
#include <fstream>
#include <sstream>
#include <iostream>

const string FILE_NAME = "account_list.txt";

using namespace std;

void WelcomeDisplay(Choice& choice){
	int userChoice = 0;
	cout << "Welcome !" << endl <<
			"1. Sign in." << endl <<
			"2. Sign up." << endl <<
			"->your choice: ";
	cin >> userChoice;
	switch(userChoice){
	case 1:
		choice = Choice::Login;
		break;
	case 2:
		choice = Choice::Register;
		break;
	default:
		choice = Choice::Nothing;
		break;
	}
}

void UsermenuDisplay(Choice& choice){
	int userChoice = 0;
	cout << "Hello user!" << endl <<
			"1. Change your password." << endl <<
			"2. Delete your account." << endl <<
			"->your choice: ";
	cin >> userChoice;
	switch(userChoice){
		case 1:
			choice = Choice::Change;
			break;
		case 2:
			choice = Choice::Delete;
			break;
		default:
			choice = Choice::Nothing;
			break;
		}
}

void AdminmenuDisplay(Choice& choice){
	int adminChoice = 0;
	cout << "Hello admin!" << endl <<
			"1. Change your password." << endl <<
			"2. Review pending accounts [" << NumberOfAccounts(Status::Pending) << "]." << endl <<
			"3. List all accounts." << endl <<
			"-> your choice: ";
	cin >> adminChoice;
	switch(adminChoice){
	case 1:
		choice = Choice::Change;
		break;
	case 2:
		choice = Choice::Review;
		break;
	case 3:
		choice = Choice::Listing;
		break;
	default:
		choice = Choice::Nothing;
		break;
	}

}

void ReviewmenuDisplay(Choice& choice){
	int adminChoice = 0;
	cout << "\nReview Menu:" << endl <<
			"1. Select account(s) for delete approval." << endl <<
			"2. Select account(s) for re-activation." << endl <<
			"3. Delete all." << endl <<
			"4. Re-activate all." << endl <<
			"-> your choice: ";
	cin >> adminChoice;
	switch(adminChoice){
		case 1:
			choice = Choice::Delete_Aprroval;
			break;
		case 2:
			choice = Choice::Reactivate;
			break;
		case 3:
			choice = Choice::Delete_All;
			break;
		case 4:
			choice = Choice::Reactivate_All;
			break;
		default:
			choice = Choice::Nothing;
			break;
		}
}

vector<string> GetFromDatabase(string id) {
	vector<string> accountInfo;
	ifstream readFile(FILE_NAME);
	string line = "";

	while (getline(readFile, line)) {
		string storedUsername = "";
		string storedPassword = "";
		string storedRole = "";
		string storedStatus = "";

		stringstream toBeCompared(line);
		toBeCompared >> storedUsername >> storedPassword >> storedRole >> storedStatus;

		if (storedUsername == id) {
			accountInfo.push_back(storedUsername);
			accountInfo.push_back(storedPassword);
			accountInfo.push_back(storedRole);
			accountInfo.push_back(storedStatus);
			break;
		}
	}
	return accountInfo;
}

vector<Account> GetFromDatabase(Status accountStatus){

	vector<Account> accountList;
	ifstream readFile(FILE_NAME);
	string line = "";

	while (getline(readFile, line)) {
		string storedUsername = "";
		string storedPassword = "";
		string storedRole = "";
		string storedStatus = "";
		vector<string> accountInfo;

		stringstream toBeCompared(line);
		toBeCompared >> storedUsername >> storedPassword >> storedRole >> storedStatus;

		accountInfo.push_back(storedUsername);
		accountInfo.push_back(storedPassword);
		accountInfo.push_back(storedRole);
		accountInfo.push_back(storedStatus);

		switch(accountStatus){
		case Status::Active:{
			if(storedStatus == "Active"){
				Account activeAccount;
				activeAccount.set(accountInfo);
				accountList.push_back(activeAccount);
			}
			break;
		}
		case Status::Deleted:{
			if (storedStatus == "Deleted") {
				Account deletedAccount;
				deletedAccount.set(accountInfo);
				accountList.push_back(deletedAccount);
			}
			break;
		}
		default:
			if(storedStatus == "Pending"){
				Account pendingAccount;
				pendingAccount.set(accountInfo);
				accountList.push_back(pendingAccount);
			}
			break;
		}
	}
	return accountList;
}

vector<Account> GetFromDatabase(){
	vector<Account> accountList;
	ifstream readFile(FILE_NAME);
	string line = "";

	while (getline(readFile, line)) {
		string storedUsername = "";
		string storedPassword = "";
		string storedRole = "";
		string storedStatus = "";
		vector<string> accountInfo;

		stringstream toBeCompared(line);
		toBeCompared >> storedUsername >> storedPassword >> storedRole >> storedStatus;

		accountInfo.push_back(storedUsername);
		accountInfo.push_back(storedPassword);
		accountInfo.push_back(storedRole);
		accountInfo.push_back(storedStatus);

		Account account;
		account.set(accountInfo);
		accountList.push_back(account);
	}
	return accountList;
}

void PushToDatabase(Account& account){
	ofstream outFile;
	vector<string> accountInfo = account.getInfo();//fetch account information to a container
	outFile.open(FILE_NAME, std::ios_base::app);//append instead of overwrite
	outFile << "\n" <<
			   accountInfo[0] << " " <<
			   accountInfo[1] << " " <<
			   accountInfo[2] << " " <<
			   accountInfo[3];
}

void EditInDatabase(Account& account){
	vector<string> accountInfo = account.getInfo();//fetch account information to a container
	ifstream readFile(FILE_NAME);
	ostringstream text;

	vector<string> databaseInfo = GetFromDatabase(accountInfo[0]);

	text << readFile.rdbuf();
	string content = text.str();
	content.replace(content.find(accountInfo[0]),
					string(databaseInfo[0] + databaseInfo[1] + databaseInfo[2] +
							databaseInfo[3]).length() + (databaseInfo.size()-1),
					accountInfo[0] + " " + accountInfo[1] + " " +
					accountInfo[2] + " " + accountInfo[3]);
	readFile.close();

	ofstream outFile(FILE_NAME);
	outFile << content;
}

void RemoveFromDatabase(vector<Account>& accountList){
	ifstream readFile(FILE_NAME);
	ostringstream text;

	text << readFile.rdbuf();
	string content = text.str();

	vector<Account>::iterator accountListIterator = accountList.begin();
	while (accountListIterator < accountList.end()) {
		vector<string> accountInfo = accountListIterator->getInfo();
		accountListIterator++;
		content.replace(content.find(accountInfo[0])-1,
						string(accountInfo[0] + accountInfo[1] + accountInfo[2] +
							   accountInfo[3]).length() + (accountInfo.size()),
						"");
	}
	readFile.close();

	ofstream outFile(FILE_NAME);
	outFile << content;
}

unsigned int NumberOfAccounts(Status status) {
	unsigned int accountCount = 0;
	ifstream readFile(FILE_NAME);
	string line = "";

	while (getline(readFile, line)) {
		string storedUsername = "";
		string storedPassword = "";
		string storedRole = "";
		string storedStatus = "";

		stringstream toBeCompared(line);
		toBeCompared >> storedUsername >> storedPassword >> storedRole >> storedStatus;

		switch (status) {
		case Status::Active: {
			if (storedStatus == "Active")
				accountCount++;
			break;
		}
		case Status::Deleted: {
			if (storedStatus == "Deleted")
				accountCount++;
			break;
		}
		case Status::Pending: {
			if (storedStatus == "Pending")
				accountCount++;
			break;
		}
		default:
			break;
		}
	}
	return accountCount;
}

bool LowerCheck(string toBeChecked){
	bool found = false;
	for (char isBeingChecking : toBeChecked) {
		if (islower(isBeingChecking)) {
			found = true;
			break;
		}
	}
	return found;
}

bool UpperCheck(string toBeChecked){
	bool found = false;
	for (char isBeingChecking : toBeChecked) {
		if (isupper(isBeingChecking)) {
			found = true;
			break;
		}
	}
	return found;
}

bool SpecialCharCheck(string toBeChecked){
	bool found = false;
	for (char isBeingChecking : toBeChecked) {

		if (!(isupper(isBeingChecking)) &&
			!(islower(isBeingChecking)) &&
			!(isdigit(isBeingChecking))) {

			found = true;
			break;
		}
	}
	return found;
}


bool PasswordCriteriaCheck(string toBeChecked){
	bool checkedOK = false;

	if(toBeChecked.size() < 8)
		cout << "Your password needs at least 8 characters!" << endl;
	if(!LowerCheck(toBeChecked))
		cout << "Your password needs at least one lowercase character!" << endl;
	if(!UpperCheck(toBeChecked))
		cout << "Your password needs at least one uppercase character!" << endl;
	if(!SpecialCharCheck(toBeChecked))
		cout << "Your password needs at least one special character!" << endl;
	if((toBeChecked.size() >= 8) &&
		LowerCheck(toBeChecked) &&
	    UpperCheck(toBeChecked) &&
	    SpecialCharCheck(toBeChecked))
			checkedOK = true;

	return checkedOK;
}

