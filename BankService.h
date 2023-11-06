#pragma once


class BankService {
	friend class Client;
protected:
	int years;
	double percent; // в формате 1.XX..
	double body;

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
public:

	void setYear(int newYear) {
		this->years = newYear;
	}
	void setBody(double newBody) {
		this->body = newBody;
	}
	void setPercent(double newPercent) {
		this->percent = newPercent;
	}

	int getYears() {
		return this->years;
	}
	double getPercent() {
		return this->percent;
	}
	double getBody() {
		return this->body;
	}

	virtual void showInConsole() {};

};
