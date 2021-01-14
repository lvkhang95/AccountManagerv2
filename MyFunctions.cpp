/*
 * MyFunctions.cpp
 *
 *  Created on: Jan 14, 2021
 *      Author: khang.le
 */
#include "MyFunctions.h"
#include <fstream>
#include <sstream>

const string FILE_NAME = "account_list.txt";

using namespace std;

vector<string> GetFromDatabase(string id) {
	vector<string> accountInfo;
	ifstream readFile(FILE_NAME);
	string line = "";

	while (getline(readFile, line)) {
		string storedUsername = "";
		string storedPassword = "";
		string storedRole = "";
		string storedStatus = "";

		stringstream toBeCompared(line);
		toBeCompared >> storedUsername >> storedPassword >> storedRole
				>> storedStatus;

		if (storedUsername == id) {
			accountInfo.push_back(storedUsername);
			accountInfo.push_back(storedPassword);
			accountInfo.push_back(storedRole);
			accountInfo.push_back(storedStatus);
			break;
		}
	}
	return accountInfo;
}



