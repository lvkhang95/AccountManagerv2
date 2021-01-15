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

enum class Choice {Nothing, Login, Register, Change, Delete};

void WelcomeDisplay(Choice&);
void UsermenuDisplay(Choice&);
vector<string> GetFromDatabase(string);
void PushToDatabase(Account&);
void EditInDatabase(Account&);
bool PasswordCriteriaCheck(string);
bool UpperCheck(string);
bool LowerCheck(string);
bool SpecialCharCheck(string);




#endif /* MYFUNCTIONS_H_ */
