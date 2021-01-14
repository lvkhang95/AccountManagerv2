/*
 * Display.cpp
 *
 *  Created on: Jan 14, 2021
 *      Author: khang.le
 */
#include <iostream>
#include "Display.h"
#include "Account.h"
using namespace std;


void WelcomeDisplay(Choice& choice){
	int userChoice = 0;
	cout << "Welcome !" << endl <<
			"1. Sign in." << endl <<
			"2. Sign up." << endl <<
			"your choice: ";
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

void LoginDisplay(Account& loginUser){

}

void RegistrationDisplay(Account& newUser){

}
