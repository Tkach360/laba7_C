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
	void setContrib(double newContrib) {
		contrib = newContrib;
	}


public:
	Credit() : BankService() {};
	Credit(int years) : BankService(years) {};
	Credit(double body) : BankService(body) {};
	Credit(int years, double percent, double body, double contrib) : BankService(years, percent, body) {
		this->contrib = contrib;
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

		for (int i = 0; i < years + 1; i++) {
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

	friend ostream& operator << (ostream& output, Credit& credit) {
		string Info = "Credit year: " + to_string(credit.years) + " body: " + to_string(credit.body) +
			" percent: " + to_string(credit.percent) + " contribution: " + to_string(credit.contrib);
		cout << Info << endl;

		return output;
	}

	// перегрузка оператора + для Credit
	friend Credit& operator + (Credit& firstCredit, Credit& secondCredit) {
		double newBody = firstCredit.getBody() + secondCredit.getBody();
		int newYears = firstCredit.getYears() + secondCredit.getYears();

		double newPercent = firstCredit.getPercent() * (firstCredit.getBody() / newBody) + secondCredit.getPercent() * (secondCredit.getBody() / newBody);
		double newContrib = getRegularContribution(newYears, newBody, newPercent);

		Credit newCredit(newYears, newPercent, newBody, newContrib);
		return newCredit;
	}

	// перегрузка оператора ++ (префиксная форма)
	Credit& operator ++ () {
		this->years += 1;
		this->contrib = getRegularContribution(this->years, this->body, this->percent);
		return *this;
	}

	// перегрузка оператора ++ (постфиксная форма)
	Credit& operator ++ (int) {
		Credit temp = *this;
		++(*this);
		return temp;
	}

	// статическая функция расчета регулярных выплат по кредиту
	static double getRegularContribution(int years, double body, double percent) {

		double clean_percent = percent - 1.0;

		double contrib = body * (clean_percent + (clean_percent / (pow(clean_percent + 1.0, (double) years) - 1)));

		contrib += 0.01; // для ликвидации ошибки связанной с машинным представлением числел

		return contrib;
	}

	static void setMaxCreditAmout(int newAmout) {
		maxCreditAmout = newAmout;
	}
	static double getMaxCreditAmout() {
		return maxCreditAmout;
	}

	// статический метод проверки кредита через Credit
	static bool isValidCredit(Credit credit) {
		if (!(credit.getYears() > 0 && credit.getBody() > credit.getContrib() && credit.getPercent() > 1)) return false;
		if (credit.getBody() * (credit.getPercent() - 1) > credit.getContrib()) return false;
		if (credit.getBody() > maxCreditAmout) return false;

		int TrueYears = 0;
		double body = credit.getBody();
		for (TrueYears; body > 0; TrueYears++) {
			body = body * credit.getPercent();
			body -= credit.getContrib();
		}
		if (TrueYears != credit.getYears()) return false;

		return true;
	}  

	// статический метод проверки кредита через параметры
	static bool isValidCredit(int years, double body, double percent, double contribution) {
		if (!(years > 0 && body > contribution && percent > 1)) return false;
		if (body * (percent - 1.0) > contribution) return false;
		if (body > maxCreditAmout) return false;

		int TrueYears = 0;
		double body_credit = body;
		for (TrueYears; body_credit > 0; TrueYears++) {
			body_credit = body_credit * percent;
			body_credit -= contribution;
		}
		if (TrueYears != years) return false;

		return true;
	}
};

double Credit::maxCreditAmout = 100000;