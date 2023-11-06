#pragma once


class BankService {
	friend class Client;
protected:
	int Years;
	double Percent; // в формате 1.XX..
	double Body;

	BankService() {
		this->Years = -1;
		this->Percent = -1;
		this->Body = -1;
	}
	BankService(int Years) {
		this->Years = Years;
		this->Percent = -1;
		this->Body = -1;
	}
	BankService(double Body) {
		this->Body = Body;
		this->Years = -1;
		this->Percent = -1;
	}
	BankService(int Years, double Percent, double Body) {
		this->Years = Years;
		this->Percent = Percent;
		this->Body = Body;
	}
public:

	void SetYear(int newYear) {
		this->Years = newYear;
	}
	void SetBody(double newBody) {
		this->Body = newBody;
	}
	void SetPercent(double newPercent) {
		this->Percent = newPercent;
	}

	int GetYears() {
		return this->Years;
	}
	double GetPercent() {
		return this->Percent;
	}
	double GetBody() {
		return this->Body;
	}

};
