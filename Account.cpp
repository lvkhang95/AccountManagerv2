/*
 * Account.cpp
 *
 *  Created on: Jan 14, 2021
 *      Author: khang.le
 */

#include "Account.h"
#include "Admin.h"
#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Account::Account() {
	// TODO Auto-generated constructor stub

}

Account::~Account() {
	// TODO Auto-generated destructor stub
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

void Account::create(){

}
