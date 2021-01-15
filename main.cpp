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
#include <iostream>

using namespace std;

int main(){
	Choice userChoice = Choice::Nothing;

	WelcomeDisplay(userChoice);

	switch(userChoice){
	case Choice::Login:
	{
		Account loginUser;
		if(loginUser.login()){
			vector<string> loggedinAccountInfo = loginUser.getInfo();
			if(loggedinAccountInfo[2] == "Admin"){
				//do admin stuff
			}
			else{
				//do user stuff
				User loggedinUser;
				loggedinUser.set(loggedinAccountInfo);
				UsermenuDisplay(userChoice);
				switch(userChoice){
				case Choice::Change:{
					//change password
					if(loggedinUser.change())
						EditInDatabase(loggedinUser);
					break;
				}
				case Choice::Delete:{
					//delete user account
					break;
				}
				default:
					break;
				}
			}
		}

		break;
	}
	case Choice::Register:
	{
		Account newUser;
		if(newUser.create())
			PushToDatabase(newUser);
		break;
	}
	default:
		break;
	}

}



