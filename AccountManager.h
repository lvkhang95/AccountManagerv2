/*
 * AccountManager.h
 *
 *  Created on: Jan 18, 2021
 *      Author: khang.le
 */

#ifndef ACCOUNTMANAGER_H_
#define ACCOUNTMANAGER_H_
#include "Account.h"

class AccountManager {
public:
	AccountManager();
	bool create(Account&);
	bool login(Account&);
	bool changePassword(Account&);
	void printInfo(Account&);
	bool deactivate(Account&);
	void reactivate(vector<Account>&);
	bool remove(vector<Account>&);
	vector<Account> listing(Status);
	void listing(vector<Account>);
	vector<Account> select(string, vector<Account>&);
};

#endif /* ACCOUNTMANAGER_H_ */
