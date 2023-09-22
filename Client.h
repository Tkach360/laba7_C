#pragma once

#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

enum TransactionResult {
	InsufficientFunds, // недостаточно средств
	NegativeAmount, // отрицательная сумма
	OK // все ок
};

struct Transaction {
	double money;
	string CounterName;
	int CounterAccountId;
	tm Time;
};

struct Account {
	int id;
	double money;
	std::vector<Transaction> Transactions;

	string ClientName; // нужно чтобы при использовании NewTransaction не передавать ещё и имя
};

struct Deposit {
	int year;
	double percent; // в формате 1.XX..
	double body;
};

struct Credit {
	int year;
	double percent; // в формате 1.XX..
	double body;
	double contribution;
};

struct Client {
	int Age;
	string Name;
	string PhoneNumber;

	vector<Credit> Credits;
	vector<Deposit> Deposits;
	vector<Account> Accounts;
};