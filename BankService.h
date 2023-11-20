#pragma once
#include "Client.h"
#include "AbstractBankService.h"

class BankService : public AbstractBankService {
	friend class Client;

protected: // использование модификатора protected

	int years;
	double percent; // в формате 1.XX..
	double body;

	void setYear(int newYear) {
		this->years = newYear;
	}
	void setBody(double newBody) {
		this->body = newBody;
	}
	void setPercent(double newPercent) {
		this->percent = newPercent;
	}


public:
	BankService() {
		this->years = -1;
		this->percent = -1;
		this->body = -1;
	}
	BankService(int years) {
		this->years = years;
		this->percent = -1;
		this->body = -1;
	}
	BankService(double body) {
		this->body = body;
		this->years = -1;
		this->percent = -1;
	}
	BankService(int years, double percent, double body) {
		this->years = years;
		this->percent = percent;
		this->body = body;
	}

	int getYears() override {
		return this->years;
	}
	double getPercent() override {
		return this->percent;
	}
	double getBody() override {
		return this->body;
	}

	double getInterestAmount() override {
		double interestAmount = 0;
		for (int i = 0; i < this->getYears(); i++)
			interestAmount += this->getBody() * (this->getPercent() - 1);
		return interestAmount;
	}
	void setNewData(int years, double percent, double body) {
		this->setYear(years);
		this->setPercent(percent);
		this->setBody(body);
	}

	// виртуальная функция начисления штрафа в виде процента от суммы задолженности
	virtual void applyPenalty(double penaltyPercent) { // в формате 0.0...
		cout << "A fine of BankService " << this->getBody() * penaltyPercent << endl;
		this->setBody(this->getBody() * (1 - penaltyPercent));
	}
};
