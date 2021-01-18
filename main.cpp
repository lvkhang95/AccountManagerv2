/*
 * main.cpp
 *
 *  Created on: Jan 14, 2021
 *      Author: khang.le
 */
#include "MyFunctions.h"
#include "Account.h"
#include "AccountManager.h"
#include "Admin.h"
#include "User.h"
#include <iostream>

using namespace std;

int main(){
	Choice userChoice = Choice::Nothing;
	Choice adminChoice = Choice::Nothing;

	WelcomeDisplay(userChoice);

	switch(userChoice){
	case Choice::Login:
	{
		Account loginUser;
		AccountManager user;
		if(user.login(loginUser)){
			vector<string> loggedinAccountInfo = loginUser.getInfo();
			if(loggedinAccountInfo[2] == "Admin"){
				//do admin stuff
				Admin loggedinAdmin;
				AccountManager admin;
				loggedinAdmin.set(loggedinAccountInfo);
				AdminmenuDisplay(adminChoice);
				switch(adminChoice){
				case Choice::Change:{
					if (admin.changePassword(loggedinAdmin))
						EditInDatabase (loggedinAdmin);
					break;
				}
				case Choice::Review:{
					admin.listing(Status::Pending);
					ReviewmenuDisplay(adminChoice);
					switch(adminChoice){
					case Choice::Delete_Aprroval:{
						vector<Account> accountList = admin.listing(Status::Pending);
						string selectedAccount = "";
						cout << "Selected account(s), separated by a semicolon(;): ";
						cin >> selectedAccount;
						vector<Account> selectedAccounts;// = admin.select(selectedAccount,accountList);
						RemoveFromDatabase(selectedAccounts);
						break;
					}
					case Choice::Reactivate:{
						admin.listing(Status::Pending);
						string selectedAccount = "";
						cout << "Selected account(s), separated by a semicolon(;): ";
						cin >> selectedAccount;
						break;
					}
					case Choice::Delete_All:{
						break;
					}
					case Choice::Reactivate_All:{
						break;
					}
					default:
						break;
					}
				}
				case Choice::Listing:{

				}
				default:
					break;
				}
			}
			else{
				//do user stuff
				User loggedinUser;
				AccountManager user;
				loggedinUser.set(loggedinAccountInfo);
				UsermenuDisplay(userChoice);
				switch(userChoice){
				case Choice::Change:{
					//change password
					if(user.changePassword(loggedinUser))
						EditInDatabase(loggedinUser);
					break;
				}
				case Choice::Delete:{
					//delete user account
					if(user.deactivate(loggedinUser))
						EditInDatabase(loggedinUser);
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
		AccountManager account;
		if(account.create(newUser))
			PushToDatabase(newUser);
		break;
	}
	default:
		break;
	}

}



