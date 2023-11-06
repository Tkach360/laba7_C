#pragma once

#include "BankService.h"
#include <iostream>
#include <string>

using namespace std;

class Deposit : public BankService {
	friend class Client;
public:
	Deposit() : BankService() {};
	Deposit(int Years) : BankService(Years) {};
	Deposit(double Body) : BankService(Body) {};
	Deposit(int Years, double Percent, double Body) : BankService(Years, Percent, Body) {}

	double GetFinalDepositAmount() {
		double FinalDepositAmount = this->GetBody();
		int Years = this->GetYears();
		for (int i = 0; i < Years; i++) {
			FinalDepositAmount *= this->GetPercent();
		}
		return FinalDepositAmount;
	}
	void ShowInConsole() {
		string Info = "Deposit year: " + to_string(this->Years) + " body: " + to_string(this->Body) +
			" percent: " + to_string(this->Percent);
		cout << Info << endl;
	}
};
