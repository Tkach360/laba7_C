#pragma once

#include "BankService.h"
#include "InputFunction.h"
#include <string>

using namespace std;

class Credit : public BankService {
	friend class Client;

private:
	static double maxCreditAmout; // максимально возможная сумма кредита

	double contrib;

public:
	Credit() : BankService() {};
	Credit(int years) : BankService(years) {};
	Credit(double body) : BankService(body) {};
	Credit(int years, double percent, double body, double contrib) : BankService(years, percent, body) {
		this->contrib = contrib;
	}

	void setContrib(double newContrib) {
		contrib = newContrib;
	}

	double getContrib() {
		return this->contrib;
	}

	double getFinalContributionsPayments() {
		double FinalContributionsPayments = 0;
		int years = getYears();
		double body = getBody();
		double percent = getPercent();
		double contribution = getContrib();
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
	void showInConsole() {
		string Info = "Credit year: " + to_string(this->years) + " body: " + to_string(this->body) +
			" percent: " + to_string(this->percent) + " contribution: " + to_string(this->contrib);
		cout << Info << endl;
	}

	static void setMaxCreditAmout(int newAmout) {
		maxCreditAmout = newAmout;
	}

	// статический метод проверки кредита через Credit
	static bool checkCredit(Credit credit) {
		if (!(credit.getYears() > 0 && credit.getBody() > credit.getContrib() && credit.getPercent() > 1)) return false;
		if (credit.getBody() * (credit.getPercent() - 1) >= credit.getContrib()) return false;
		if (credit.getBody() > maxCreditAmout) return false;

		int TrueYears = 0;
		double body = credit.getBody();
		for (TrueYears; body > 0; TrueYears++)
			body -= body * credit.getPercent();
		if (TrueYears != credit.getYears()) return false;

		return true;
	}  

	// статический метод проверки кредита через параметры
	static bool checkCredit(int years, double body, double percent, double contribution) {
		if (!(years > 0 && body > contribution && percent > 1)) return false;
		if (body * (percent - 1) >= contribution) return false;
		if (body > maxCreditAmout) return false;

		int TrueYears = 0;
		double body_credit = body;
		for (TrueYears; body_credit > 0; TrueYears++)
			body_credit -= body_credit * percent;
		if (TrueYears != years) return false;

		return true;
	}
};

double Credit::maxCreditAmout = 100000;