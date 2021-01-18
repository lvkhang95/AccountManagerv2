/*
 * MyFunctions.h
 *
 *  Created on: Jan 14, 2021
 *      Author: khang.le
 */

#ifndef MYFUNCTIONS_H_
#define MYFUNCTIONS_H_

#include "Account.h"
#include <vector>
#include <string>

using namespace std;

enum class Choice {Nothing, Login, Register, Change, Delete,
				   Review, Listing, Delete_Aprroval, Reactivate,
				   Delete_All, Reactivate_All};

void WelcomeDisplay(Choice&);
void UsermenuDisplay(Choice&);
void AdminmenuDisplay(Choice&);
void ReviewmenuDisplay(Choice&);
vector<string> GetFromDatabase(string);
vector<Account> GetFromDatabase(Status);
vector<Account> GetFromDatabase();
void PushToDatabase(Account&);
void EditInDatabase(Account&);
void RemoveFromDatabase(vector<Account>&);
unsigned int NumberOfAccounts(Status);
bool PasswordCriteriaCheck(string);
bool UpperCheck(string);
bool LowerCheck(string);
bool SpecialCharCheck(string);




#endif /* MYFUNCTIONS_H_ */
