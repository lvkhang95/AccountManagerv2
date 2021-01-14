/*
 * main.cpp
 *
 *  Created on: Jan 14, 2021
 *      Author: khang.le
 */
#include "MyFunctions.h"
#include "Account.h"
#include "Admin.h"
#include "User.h"
#include "Display.h"
#include <iostream>

using namespace std;

int main(){
	Choice userChoice = Choice::Nothing;

	WelcomeDisplay(userChoice);

	switch(userChoice){
	case Choice::Login:
		//todo
		break;
	case Choice::Register:
	{
		User newAccount;
		string newUsername;

		cout << "username :";
		cin >> newUsername;

		vector<string> accountInfo = GetFromDatabase(newUsername);
		break;
	}
	default:
		break;
	}

}



