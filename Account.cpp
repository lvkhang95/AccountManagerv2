/*
 * Account.cpp
 *
 *  Created on: Jan 14, 2021
 *      Author: khang.le
 */

#include "Account.h"
#include "Admin.h"
#include "User.h"
#include "MyFunctions.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Account::Account() {
	// TODO Auto-generated constructor stub

}

vector<string> Account::getInfo(){
	vector<string> accountInfo;
	accountInfo.push_back(username);
	accountInfo.push_back(password);

	switch(role){
	case Role::Admin:
		accountInfo.push_back("Admin");
		break;
	default:
		accountInfo.push_back("User");
		break;
	}

	switch(status){
	case Status::Active:
		accountInfo.push_back("Active");
		break;
	case Status::Deleted:
		accountInfo.push_back("Deleted");
		break;
	default:
		accountInfo.push_back("Pending");
		break;
	}
	return accountInfo;
}

void Account::set(vector<string> accountInfo){
	username = accountInfo[0];
	password = accountInfo[1];

	if(accountInfo[2] == "Admin")
		role = Role::Admin;
	else
		role = Role::User;

	if(accountInfo[3] == "Active")
		status = Status::Active;
	if(accountInfo[3] == "Deleted")
			status = Status::Deleted;
	if(accountInfo[3] == "Pending")
			status = Status::Pending;

}

bool Account::create(){
	//string newUsername;
	bool accountCreated = false;

	cout << "Create a new account" << endl <<
			"Username: ";
	cin >> this->username;

	vector<string> accountInfo = GetFromDatabase(username);
	if ((accountInfo.size() == 0) || (accountInfo[3] == "Deleted")) { //unique check
		//string newPassword = "";
		cout << "\nPassword must has at least 8 characters." << endl <<
				"Including special and upper&lower cases characters." << endl <<
				endl <<
				"Password:";
		cin >> this->password;

		bool isPasswordOK = PasswordCriteriaCheck(password);
		if (isPasswordOK) {
			string confirmPassword = "";
			cout << "Confirm password: ";
			cin >> confirmPassword;
			if (confirmPassword == password) {
				role = Role::User;
				status = Status::Active;
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

bool Account::login(){
	bool isLoggedin = false;
	cout << "Username: ";
	cin >> this->username;
	cout << "password: ";
	cin >> this->password;

	vector<string> accountInfo = GetFromDatabase(username);
	if(accountInfo.size() != 0 &&
	   accountInfo[3] == "Active" &&
	   accountInfo[1] == password){
		this->set(accountInfo);
		cout << "Login successfully!" << endl;
		isLoggedin = true;
	}
	else
		cout << "Invalid username and password!" << endl;
	return isLoggedin;
}

bool Account::change(){
	bool isChanged = false;
	string oldPassword = "";

	cout << "\nPassword must has at least 8 characters." << endl <<
			"Including special and upper&lower cases characters." << endl << endl <<
			"Old Password:";

	cin >> oldPassword;
	if (oldPassword != password)
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
				password = confirmPassword;
				isChanged = true;
				cout << "Password changed successfully!";
			}
		}
	}
	return isChanged;
}





