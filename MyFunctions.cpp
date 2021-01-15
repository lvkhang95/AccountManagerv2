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
			"2. Deleted your account." << endl <<
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
		toBeCompared >> storedUsername >> storedPassword >> storedRole
				>> storedStatus;

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

	text << readFile.rdbuf();
	string content = text.str();
	content.replace(content.find(accountInfo[0]),
					string(accountInfo[0] + accountInfo[1] + accountInfo[2] + accountInfo[3]).length() + (accountInfo.size()-1),
					accountInfo[0] + " " + accountInfo[1] + " " + accountInfo[2] + " " + accountInfo[3]);
	readFile.close();

	ofstream outFile(FILE_NAME);
	outFile << content;
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

