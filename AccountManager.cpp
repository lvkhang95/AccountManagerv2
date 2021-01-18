/*
 * AccountManager.cpp
 *
 *  Created on: Jan 18, 2021
 *      Author: khang.le
 */

#include "AccountManager.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "MyFunctions.h"

AccountManager::AccountManager() {
	// TODO Auto-generated constructor stub

}

bool AccountManager::create(Account& account){
	bool accountCreated = false;
	string newUsername = "";

	cout << "Create a new account" << endl <<
			"Username: ";
	cin >> newUsername;

	vector<string> accountInfo = GetFromDatabase(newUsername);
	if ((accountInfo.size() == 0) || (accountInfo[3] == "Deleted")) { //unique check
		accountInfo.push_back(newUsername); // 1st elem of the container is the username
		cout << "\nPassword must has at least 8 characters." << endl <<
				"Including special and upper&lower cases characters." << endl <<
				endl <<
				"Password:";
		string newPassword = "";
		cin >> newPassword;
		accountInfo.push_back(newPassword);// 2nd elem of the container is the password

		bool isPasswordOK = PasswordCriteriaCheck(accountInfo[1]);
		if (isPasswordOK) {
			string confirmPassword = "";
			cout << "Confirm password: ";
			cin >> confirmPassword;
			if (confirmPassword == accountInfo[1]) {
				accountInfo.push_back("User"); // 3rd elem of the container is the role
				accountInfo.push_back("Active"); // 4th elem of the container is the status
				account.set(accountInfo); // push new account info to an object
				accountCreated = true;
				cout << "An Account is successfully created!";
			} else
				cout << "Your confirm password is not correct!";
		} else
			cout << "Please try again!";
	} else
		cout << "Your username is used.";
	return accountCreated;
}

bool AccountManager::login(Account& account){
	bool isLoggedin = false;
	string loginUsername = "";
	string loginPassword = "";
	cout << "Username: ";
	cin >> loginUsername;
	cout << "password: ";
	cin >> loginPassword;

	vector<string> accountInfo = GetFromDatabase(loginUsername);
	if(accountInfo.size() != 0 &&
	   accountInfo[3] == "Active" &&
	   accountInfo[1] == loginPassword){
		account.set(accountInfo);
		cout << "Login successfully!" << endl;
		isLoggedin = true;
	}
	else
		cout << "Invalid username and password!" << endl;
	return isLoggedin;
}

bool AccountManager::changePassword(Account& account){
	bool isChanged = false;
	string oldPassword = "";
	vector<string> accountInfo = account.getInfo();

	cout << "\nPassword must has at least 8 characters." << endl <<
			"Including special and upper&lower cases characters." << endl << endl <<
			"Old Password:";

	cin >> oldPassword;
	if (oldPassword != accountInfo[1])
		cout << "Your old password is not correct!" << endl;
	else{
		string newPassword = "";
		cout << "New Password: ";
		cin >> newPassword;
		bool isPasswordOK = PasswordCriteriaCheck(newPassword);
		if (isPasswordOK) {
			string confirmPassword = "";
			cout << "Confirm password: ";
			cin >> confirmPassword;
			if (confirmPassword == newPassword){
				accountInfo[1] = confirmPassword;
				account.set(accountInfo);
				isChanged = true;
				cout << "Password changed successfully!";
			}
		}
	}
	return isChanged;
}

void AccountManager::printInfo(Account& account){
	vector<string> accountInfo = account.getInfo();
	cout << "Username: " << accountInfo[0] << endl;
	cout << "Password: " << accountInfo[1] << endl;
	cout << "Role: " << accountInfo[2] << endl;
	cout << "Status: " << accountInfo[3] << endl;
}

bool AccountManager::deactivate(Account& account){
	bool isDeactivate = false;
	string password ="";
	cout << "Re-enter your password: ";
	cin >> password;
	vector<string> accountInfo = account.getInfo();
	if(password == accountInfo[1]){
		accountInfo[3] = "Pending";
		account.set(accountInfo);
		isDeactivate = true;
		cout << "Your request is sent.";
	}
	else
		cout << "Incorrect password !!!";
	return isDeactivate;
}

bool AccountManager::remove(vector<Account>& deletedAccounts){
	bool isDeleted = false;
	string deleteConfirmation = "";
	vector<Account>::iterator deletedAccountIt = deletedAccounts.begin();
	cout << "Account(s) to be deleted:" << endl;
	this->listing(deletedAccounts);
	cout << "Are you sure ? <y/n>" << endl;
	cin >> deleteConfirmation;
	if(deleteConfirmation == "y" || deleteConfirmation == "yes"){
		RemoveFromDatabase(deletedAccounts);
		cout << "Successfully deleted " << deletedAccounts.size() << "account(s) from database !!!" << endl;
		isDeleted = true;
	}
	return isDeleted;
}
vector<Account> AccountManager::listing(Status accountStatus){
	vector<Account> accountList;
	switch(accountStatus){
	case Status::Active:{
		accountList = GetFromDatabase(Status::Active);
		break;
	}
	case Status::Deleted:{
		accountList = GetFromDatabase(Status::Deleted);
		break;
	}
	case Status::Pending:{
		accountList = GetFromDatabase(Status::Pending);
		break;
	}
	default:
		break;
	}
	this->listing(accountList);
	return accountList;
}

void AccountManager::listing(vector<Account> accountList){
	unsigned int accountCount = 0;
	vector<Account>::iterator accountListIterator = accountList.begin();
	while (accountListIterator < accountList.end()) {
		vector<string> accountInfo = accountListIterator->getInfo();
		cout << ++accountCount << ". " << accountInfo[0] << endl;
		accountListIterator++;
	}
}

vector<Account> select(string selection,vector<Account> sourceAccounts){
	vector<Account> selectedAccounts;
	string::iterator it = selection.begin();
	string elementh = "";
	while(it < selection.end()){
		if(isdigit(*it))
			elementh.push_back(*it);
		else{
			stringstream ss(elementh); //convert string to int
			int iterator = 0;
			ss >> iterator;
			selectedAccounts.push_back(sourceAccounts[iterator-1]);
			elementh.erase();
		}
	}
	return selectedAccounts;
}
