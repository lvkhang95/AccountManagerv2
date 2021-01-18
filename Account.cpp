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






