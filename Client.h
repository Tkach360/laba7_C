#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include "Client.cpp"

using namespace std;

enum TransactionResult {
	InsufficientFunds, // недостаточно средств
	NegativeAmount, // отрицательная сумма
	OK // все ок
};

class Transaction {
private:
	double money;
	string CounterName;
	int CounterAccountId;
	tm Time;

public:

};

class Account {
private:
	int id;
	double money;
	std::vector<Transaction> Transactions;

	string ClientName; // нужно чтобы при использовании NewTransaction не передавать ещё и имя

public:

};

class Deposit {
private:
	int year;
	double percent; // в формате 1.XX..
	double body;

public:

};

class Credit {
private:
	int year;
	double percent; // в формате 1.XX..
	double body;
	double contribution;

public:

};

class Client {
private:
	int Age;
	string Name;
	string PhoneNumber;

	vector<Credit> Credits;
	vector<Deposit> Deposits;
	vector<Account> Accounts;

public:
	Client();
	Client(string name, int age, string PhoneNumber) {
		Name = name;
		Age = age;
		PhoneNumber = PhoneNumber;
	}

	string GetName() {
		return Name;
	}
	string GetPhoneNumber() {
		return PhoneNumber;
	}
	int GetAge() {
		return Age;
	}

	void InputClientFromConsole() {
		string Name, PhoneNumber;
		int Age;
		Name = InputClientName("Enter the name of the new client (First Name Last Name): ");
		Age = InputInt("Enter the age of the new client: ");
		PhoneNumber = InputClientPhoneNumber("Enter the phone number of the new client (X-XXX-XXX-XX-XX): ");

		cout << "Client successfully registered" << endl;
		Client(Name, Age, PhoneNumber);
	}
};

//---------------------------------------Account--------------------------------------

void NewAccount(Client* client, double money);
void InputNewAccountFromConsole(Client* client);
int GetAccountId(Account account);
double GetMoney(Account account);

//------------------------Get-Credit-and-Deposit---------------------------------------
int GetYear(Credit credit);
int GetYear(Deposit deposit);

double GetBody(Credit credit);
double GetBody(Deposit deposit);

double GetPercent(Credit credit);
double GetPercent(Deposit deposit);

//-------------------------------------Credit-----------------------------------------

void NewCredit(Client* client, int years, double body, double percent, double contribution);
void InputNewCreditFromConsole(Client* client);

double GetContribution(Credit credit);
double GetFinalContributionsPayments(Credit credit);

//--------------------------------------Deposit------------------------------------------

void NewDeposit(Client* client, int year, double body, double percent);
void InputNewDepositFromConsole(Client* client);

double GetFinalDepositAmount(Deposit deposit);

//-----------------------------------------------Transaction-------------------------

TransactionResult NewTransaction(Account* Account_1, Account* Account_2, double transactionMoney);
void InputNewTransactionFromConsole(Account* Account_1, Account* Account_2);