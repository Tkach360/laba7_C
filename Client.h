#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include "Account.h"
#include "Deposit.h"
#include "Credit.h"

using namespace std;

class Client {
private:
	int age;
	string name;
	string phoneNumber;

public:
	vector<Credit> Credits;
	vector<Deposit> Deposits;
	vector<Account> Accounts;

	Client() {
		this->name = "NONE";
		this->age = -1;
		this->phoneNumber = "NONE";
	}
	Client(string name) {
		this->name = name;
		this->age = -1;
		this->phoneNumber = "NONE";
	}
	Client(int age) {
		this->age = age;
		this->name = "NONE";
		this->phoneNumber = "NONE";
	}
	Client(string name, int age, string phoneNumber) {
		this->name = name;
		this->age = age;
		this->phoneNumber = phoneNumber;
	}

	string getName() {
		return this->name;
	}
	string getPhoneNumber() {
		return this->phoneNumber;
	}
	int getAge() {
		return this->age;
	}
	Account getAccountByID(int ID) {
		return Accounts[ID];
	}

	void setPhoeNumber(string phoneNumber) {
		this->phoneNumber = phoneNumber;
	}
	void setAge(int age) {
		this->age = age;
	}
	void setName(string name) {
		this->name = name;
	}

	void inputClientFromConsole() {
		this->name = inputClientName("Enter the name of the new client (First name Last name): ");
		this->age = inputInt("Enter the age of the new client: ");
		this->phoneNumber = inputClientPhoneNumber("Enter the phone number of the new client (X-XXX-XXX-XX-XX): ");

		cout << "Client successfully registered" << endl;
	}

	void addNewAccount(double money) {
		Account newAccount(this, Accounts.size(), money);
		this->Accounts.push_back(newAccount);
	}
	void inputNewAccountFromConsole() {
		double money = inputDouble("Enter the initial amount in the account: ");

		addNewAccount(money);
		cout << "Account created successfully" << endl;
	}

	void addNewCredit(int Year, double Percent, double Body, double Contrib) {
		Credit newCredit(Year, Percent, Body, Contrib);
		this->Credits.push_back(newCredit);
	}
	void addNewCredit(Credit newCredit) {
		this->Credits.push_back(newCredit);
	}
	void inputNewCreditFromConsole() {
		Credit newCredit;
		newCredit.setYear(inputInt("Enter the number of years for which you want to take out a loan: "));
		newCredit.setBody(inputDouble("Enter the loan amount: "));
		do {
			newCredit.setPercent(inputDouble("Enter the loan interest (1.XX..): "));
			if (newCredit.getPercent() < 1) cout << "percentage cannot be less than 1" << endl;
		} while (newCredit.getPercent() < 1);
		newCredit.setContrib(inputDouble("Enter the monthly payment amount: "));

		addNewCredit(newCredit);
		cout << "Loan taken successfully" << endl;
	}

	void addNewDeposit(int Year, double Percent, double Body) {
		Deposit newDeposit(Year, Percent, Body);
		this->Deposits.push_back(newDeposit);
	}
	void addNewDeposit(Deposit newDeposit) {
		this->Deposits.push_back(newDeposit);
	}
	void inputNewDepositFromConsole() {
		Deposit newDeposit;
		newDeposit.setYear(inputInt("Enter the number of years for which you want to open a deposit: "));
		newDeposit.setBody(inputDouble("Enter the deposit amount: "));
		do {
			newDeposit.setPercent(inputDouble("Enter the interest accrued per year on the deposit (1.XX..): "));
			if (newDeposit.getPercent() < 1) cout << "percentage cannot be less than 1" << endl;
		} while (newDeposit.getPercent() < 1);

		addNewDeposit(newDeposit);
		cout << "Money has been successfully deposited" << endl;
	}

	double getAllAccountsMoney() {
		double AllAccountsMoney = 0;
		for (Account account : Accounts) {
			AllAccountsMoney += account.getBalance();
		}
		return AllAccountsMoney;
	}
	vector<Transaction> getAllTransactions() {
		vector<Transaction> AllTransactions;
		for (Account account : Accounts)
			AllTransactions.insert(AllTransactions.end(), account.Transactions.begin(), account.Transactions.end());
		return AllTransactions;
	}
	void showInConsole() {
		cout << "Name: " + this->name + " age: " + to_string(this->age) + " Phone number: " +
			this->phoneNumber << endl;
		cout << "  Accounts: " + to_string(this->Accounts.size()) + " Credits: " +
			to_string(this->Credits.size()) + " Deposits: " + to_string(this->Deposits.size()) << endl;
	}
	vector<Account> getAllAccounts() {
		return this->Accounts;
	}
	vector<Deposit> getAllDeposits() {
		return this->Deposits;
	}
	vector<Credit> getAllCredits() {
		return this->Credits;
	}
};

string Account::getClientName() {
	return this->client->getName();
}

void Account::inputNewTransactionFromConsole(Account* AlterAccount) {
	string message = "Enter the amount you wish to transfer from " + this->client->getName() +
		" account number " + to_string(this->getID()) + " to " + AlterAccount->getClientName() +
		" account number " + to_string(AlterAccount->getID()) + ": ";

	double transactionMoney;
	bool flag;
	do {
		flag = false;
		transactionMoney = inputDouble(message);
		if (transactionMoney == 0) {
			cout << "The transfer amount cannot be zero" << endl;
			flag = true;
		}
		if (transactionMoney > balance) {
			cout << "Insufficient funds in the account" << endl;
			flag = true;
		}
	} while (flag);

	makeTransaction(AlterAccount, transactionMoney);
	cout << "Operation was successfully completed" << endl;
}

void Account::showInConsole() {
	string Info = "Client: " + this->client->getName() + " num: " + to_string(this->ID) +
		" balance: " + to_string(this->balance);
	cout << Info << endl;
}