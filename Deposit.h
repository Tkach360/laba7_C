#pragma once

#include "BankService.h"
#include <iostream>
#include <string>

using namespace std;

class Deposit : public BankService {

public:
	Deposit() : BankService() {};
	Deposit(int years) : BankService(years) {};
	Deposit(double Body) : BankService(Body) {};
	Deposit(int years, double Percent, double Body) : BankService(years, Percent, Body) {}

	double getFinalDepositAmount() {
		double FinalDepositAmount = this->getBody();
		int years = this->getYears();
		for (int i = 0; i < years; i++) {
			FinalDepositAmount *= this->getPercent();
		}
		return FinalDepositAmount;
	}

	friend ostream& operator << (ostream& output, Deposit& deposit) {
		string Info = "Deposit year: " + to_string(deposit.years) + " body: " + to_string(deposit.body) +
			" percent: " + to_string(deposit.percent);
		cout << Info << endl;

		return output;
	}
};
