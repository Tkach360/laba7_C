#pragma once

#include <ctime>
#include <string>

using namespace std;

class Transaction {
	friend class Account;
private:
	bool sent;
	double money;
	string alterClientName;
	int alterAccountID;
	tm Time;

	Transaction(string alterClientName, int alterAccountID, double money, bool sent) {
		this->sent = sent;
		this->alterAccountID = alterAccountID;
		this->alterClientName = alterClientName;
		this->money = money;
		time_t now = time(NULL);
		localtime_s(&this->Time, &now);
	}

public:
	bool getSent() {
		return this->sent;
	}
	double getMoney() {
		return this->money;
	}
	string getAlterClientName() {
		return alterClientName;
	}
	int getAlterAccountID() {
		return alterAccountID;
	}
	tm getTime() {
		return Time;
	}

	void showInConsole() {
		string strTime = to_string(Time.tm_mday) + "." + to_string(Time.tm_mon + 1) + "."
			+ to_string(Time.tm_year + 1900) + " " + to_string(Time.tm_hour) + ":" + to_string(Time.tm_min);
		string strMoney, strAlterClientName, strAlterAccountID;

		if (this->sent) {
			strMoney = "-" + to_string(this->money);
			strAlterClientName = "to " + this->alterClientName;
		}
		else {
			strMoney = "+" + to_string(money);
			strAlterClientName = "from " + this->alterClientName;
		}

		strAlterAccountID = to_string(alterAccountID);
		cout << "Time: " + strTime + " " + strMoney + " " + strAlterClientName + " acc. " + strAlterAccountID << endl;
	}
};