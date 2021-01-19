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
						EditInDatabase(loggedinAdmin);
					break;
				}
				case Choice::Review:{
					vector<Account> pendingAccounts = admin.listing(Status::Pending);
					ReviewmenuDisplay(adminChoice);
					switch(adminChoice){
					case Choice::Delete_Aprroval:{
						admin.listing(pendingAccounts);
						string selection = "";
						cout << "Selected account(s), separated by a semicolon(;): ";
						cin >> selection;
						vector<Account> selectedAccounts = admin.select(selection, pendingAccounts);
						RemoveFromDatabase(selectedAccounts);
						cout << "Successfully deleted!" << endl;
						break;
					}
					case Choice::Reactivate:{
						admin.listing(Status::Pending);
						string selection = "";
						cout << "Selected account(s), separated by a semicolon(;): ";
						cin >> selection;
						vector<Account> selectedAccounts = admin.select(selection, pendingAccounts);
						admin.reactivate(selectedAccounts);
						for(Account toBeReactivated : selectedAccounts)
							EditInDatabase(toBeReactivated);
						break;
					}
					case Choice::Delete_All:{
						RemoveFromDatabase(pendingAccounts);
						break;
					}
					case Choice::Reactivate_All:{
						for(Account toBeReactivated : pendingAccounts)
							EditInDatabase(toBeReactivated);
						break;
					}
					default:
						break;
					}
				}
				case Choice::Listing:{
					cout << "Active accounts:" << endl;
					admin.listing(Status::Active);
					cout << "Pending accounts:" << endl;
					admin.listing(Status::Pending);
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



