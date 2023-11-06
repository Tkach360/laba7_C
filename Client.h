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
	int Age;
	string Name;
	string PhoneNumber;

public:
	vector<Credit> Credits;
	vector<Deposit> Deposits;
	vector<Account> Accounts;

	Client() {
		this->Name = "NONE";
		this->Age = -1;
		this->PhoneNumber = "NONE";
	}
	Client(string Name) {
		this->Name = Name;
		this->Age = -1;
		this->PhoneNumber = "NONE";
	}
	Client(int Age) {
		this->Age = Age;
		this->Name = "NONE";
		this->PhoneNumber = "NONE";
	}
	Client(string Name, int Age, string PhoneNumber) {
		this->Name = Name;
		this->Age = Age;
		this->PhoneNumber = PhoneNumber;
	}

	string GetName() {
		return this->Name;
	}
	string GetPhoneNumber() {
		return this->PhoneNumber;
	}
	int GetAge() {
		return this->Age;
	}
	Account GetAccountByID(int ID) {
		return Accounts[ID];
	}

	void SetPhoeNumber(string PhoneNumber) {
		this->PhoneNumber = PhoneNumber;
	}
	void SetAge(int Age) {
		this->Age = Age;
	}
	void SetName(string Name) {
		this->Name = Name;
	}

	void InputClientFromConsole() {
		this->Name = InputClientName("Enter the name of the new client (First Name Last Name): ");
		this->Age = InputInt("Enter the age of the new client: ");
		this->PhoneNumber = InputClientPhoneNumber("Enter the phone number of the new client (X-XXX-XXX-XX-XX): ");

		cout << "Client successfully registered" << endl;
	}

	void AddNewAccount(double money) {
		Account newAccount(this, Accounts.size(), money);
		this->Accounts.push_back(newAccount);
	}
	void InputNewAccountFromConsole() {
		double money = InputDouble("Enter the initial amount in the account: ");

		AddNewAccount(money);
		cout << "Account created successfully" << endl;
	}

	void AddNewCredit(int Year, double Percent, double Body, double Contrib) {
		Credit newCredit(Year, Percent, Body, Contrib);
		this->Credits.push_back(newCredit);
	}
	void AddNewCredit(Credit newCredit) {
		this->Credits.push_back(newCredit);
	}
	void InputNewCreditFromConsole() {
		Credit newCredit;
		newCredit.SetYear(InputInt("Enter the number of years for which you want to take out a loan: "));
		newCredit.SetBody(InputDouble("Enter the loan amount: "));
		do {
			newCredit.SetPercent(InputDouble("Enter the loan interest (1.XX..): "));
			if (newCredit.GetPercent() < 1) cout << "percentage cannot be less than 1" << endl;
		} while (newCredit.GetPercent() < 1);
		newCredit.SetContrib(InputDouble("Enter the monthly payment amount: "));

		AddNewCredit(newCredit);
		cout << "Loan taken successfully" << endl;
	}

	void AddNewDeposit(int Year, double Percent, double Body) {
		Deposit newDeposit(Year, Percent, Body);
		this->Deposits.push_back(newDeposit);
	}
	void AddNewDeposit(Deposit newDeposit) {
		this->Deposits.push_back(newDeposit);
	}
	void InputNewDepositFromConsole() {
		Deposit newDeposit;
		newDeposit.SetYear(InputInt("Enter the number of years for which you want to open a deposit: "));
		newDeposit.SetBody(InputDouble("Enter the deposit amount: "));
		do {
			newDeposit.SetPercent(InputDouble("Enter the interest accrued per year on the deposit (1.XX..): "));
			if (newDeposit.GetPercent() < 1) cout << "percentage cannot be less than 1" << endl;
		} while (newDeposit.GetPercent() < 1);

		AddNewDeposit(newDeposit);
		cout << "Money has been successfully deposited" << endl;
	}

	double GetAllAccountsMoney() {
		double AllAccountsMoney = 0;
		for (Account account : Accounts) {
			AllAccountsMoney += account.GetBalance();
		}
		return AllAccountsMoney;
	}
	vector<Transaction> GetAllTransactions() {
		vector<Transaction> AllTransactions;
		for (Account account : Accounts)
			AllTransactions.insert(AllTransactions.end(), account.Transactions.begin(), account.Transactions.end());
		return AllTransactions;
	}
	void ShowInConsole() {
		cout << "Name: " + this->Name + " Age: " + to_string(this->Age) + " Phone number: " +
			this->PhoneNumber << endl;
		cout << "  Accounts: " + to_string(this->Accounts.size()) + " Credits: " +
			to_string(this->Credits.size()) + " Deposits: " + to_string(this->Deposits.size()) << endl;
	}
	vector<Account> GetAllAccounts() {
		return this->Accounts;
	}
	vector<Deposit> GetAllDeposits() {
		return this->Deposits;
	}
	vector<Credit> GetAllCredits() {
		return this->Credits;
	}
};

string Account::GetClientName() {
	return this->client->GetName();
}

void Account::InputNewTransactionFromConsole(Account* AlterAccount) {
	string message = "Enter the amount you wish to transfer from " + this->client->GetName() +
		" account number " + to_string(this->GetID()) + " to " + AlterAccount->GetClientName() +
		" account number " + to_string(AlterAccount->GetID()) + ": ";

	double transactionMoney;
	bool flag;
	do {
		flag = false;
		transactionMoney = InputDouble(message);
		if (transactionMoney == 0) {
			cout << "The transfer amount cannot be zero" << endl;
			flag = true;
		}
		if (transactionMoney > Balance) {
			cout << "Insufficient funds in the account" << endl;
			flag = true;
		}
	} while (flag);

	MakeTransaction(AlterAccount, transactionMoney);
	cout << "Operation was successfully completed" << endl;
}

void Account::ShowInConsole() {
	string Info = "Client: " + this->client->GetName() + " num: " + to_string(this->ID) +
		" balance: " + to_string(this->Balance);
	cout << Info << endl;
}