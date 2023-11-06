#pragma once

#include <ctime>
#include <string>

using namespace std;

class Transaction {
	friend class Account;
private:
	bool Sent;
	double Money;
	string AlterClientName;
	int AlterAccountID;
	tm Time;

	Transaction(string AlterClientName, int AlterAccountID, double Money, bool Sent) {
		this->Sent = Sent;
		this->AlterAccountID = AlterAccountID;
		this->AlterClientName = AlterClientName;
		this->Money = Money;
		time_t now = time(NULL);
		localtime_s(&this->Time, &now);
	}

public:
	bool GetSent() {
		return this->Sent;
	}
	double GetMoney() {
		return this->Money;
	}
	string GetAlterClientName() {
		return AlterClientName;
	}
	int GetAlterAccountID() {
		return AlterAccountID;
	}
	tm GetTime() {
		return Time;
	}

	void ShowInConsole() {
		string strTime = to_string(Time.tm_mday) + "." + to_string(Time.tm_mon + 1) + "."
			+ to_string(Time.tm_year + 1900) + " " + to_string(Time.tm_hour) + ":" + to_string(Time.tm_min);
		string strMoney, strAlterClientName, strAlterAccountID;

		if (this->Sent) {
			strMoney = "-" + to_string(this->Money);
			strAlterClientName = "to " + this->AlterClientName;
		}
		else {
			strMoney = "+" + to_string(Money);
			strAlterClientName = "from " + this->AlterClientName;
		}

		strAlterAccountID = to_string(AlterAccountID);
		cout << "Time: " + strTime + " " + strMoney + " " + strAlterClientName + " acc. " + strAlterAccountID << endl;
	}
};