/*
 * Display.h
 *
 *  Created on: Jan 14, 2021
 *      Author: khang.le
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_
#include "Account.h"

enum class Choice {Nothing, Login, Register};

void WelcomeDisplay(Choice&);
void LoginDisplay(Account&);
void RegistrationDisplay(Account&);


#endif /* DISPLAY_H_ */
