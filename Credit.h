#pragma once

#include "BankService.h"
#include "InputFunction.h"
#include <string>

using namespace std;

class Credit : public BankService {
	friend class Client;
private:
	double Contrib;

public:
	Credit() : BankService() {};
	Credit(int Years) : BankService(Years) {};
	Credit(double Body) : BankService(Body) {};
	Credit(int Years, double Percent, double Body, double Contrib) : BankService(Years, Percent, Body) {
		this->Contrib = Contrib;
	}

	void SetContrib(double newContrib) {
		Contrib = newContrib;
	}

	double GetContrib() {
		return this->Contrib;
	}

	double GetFinalContributionsPayments() {
		double FinalContributionsPayments = 0;
		int years = GetYears();
		double body = GetBody();
		double percent = GetPercent();
		double contribution = GetContrib();
		for (int i = 0; i < years; i++) {
			if (body < contribution) {
				FinalContributionsPayments += body;
				body = 0;
			}
			else {
				FinalContributionsPayments += contribution;
				body -= contribution;
				body *= percent;
			}
		}
		return FinalContributionsPayments;
	}
	void ShowInConsole() {
		string Info = "Credit year: " + to_string(this->Years) + " body: " + to_string(this->Body) +
			" percent: " + to_string(this->Percent) + " contribution: " + to_string(this->Contrib);
		cout << Info << endl;
	}
	bool CheckThisCredit() {
		if (!(this->Years > 0 && this->Body > this->Contrib && this->Percent > 1)) return false;
		if (this->Body * (this->Percent - 1) >= this->Contrib) return false;

		int TrueYears = 0;
		double Body = this->Body;
		for (TrueYears; Body > 0; TrueYears++)
			Body -= Body * this->Percent;
		if (TrueYears != this->Years) return false;

		return true;
	}
	static bool CheckCredit(Credit credit) {
		if (!(credit.GetYears() > 0 && credit.GetBody() > credit.GetContrib() && credit.GetPercent() > 1)) return false;
		if (credit.GetBody() * (credit.GetPercent() - 1) >= credit.GetContrib()) return false;

		int TrueYears = 0;
		double Body = credit.GetBody();
		for (TrueYears; Body > 0; TrueYears++)
			Body -= Body * credit.GetPercent();
		if (TrueYears != credit.GetYears()) return false;

		return true;
	}
	static bool CheckCredit(int years, double body, double percent, double contribution) {
		if (!(years > 0 && body > contribution && percent > 1)) return false;
		if (body * (percent - 1) >= contribution) return false;

		int TrueYears = 0;
		double Body = body;
		for (TrueYears; Body > 0; TrueYears++)
			Body -= Body * percent;
		if (TrueYears != years) return false;

		return true;
	}
};