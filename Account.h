/*
 * Account.h
 *
 *  Created on: Jan 14, 2021
 *      Author: khang.le
 */
#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <string>
#include <vector>

using namespace std;

enum class Role {Admin, User};
enum class Status {Active, Pending, Deleted};

class Account {
protected:
	string username;
	string password;
	Role role;
	Status status;
public:
	Account();
	~Account();
	void create();
	vector<string> getInfo();
};

#endif /* ACCOUNT_H_ */
