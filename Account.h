#pragma once

#include "Client.h"
#include "Transaction.h"

using namespace std;

class Account {
	friend class Client;

private:
	static int nextUniqueID;  // уникальный ID

	int ID;
	double balance;
	Client* client;

	void setMoney(double newMoney) {
		this->balance = newMoney;
	}
	void addNewTransaction(Transaction<tm, int> newTransaction) {
		this->Transactions.push_back(newTransaction);
	}

public:
	vector<Transaction<tm, int>> Transactions;

	Account(Client* client) {
		this->client = client;
		this->balance = 0;
		this->ID = nextUniqueID;
		++nextUniqueID;
	}
	Account(Client* client, double balance) {
		this->client = client;
		this->balance = balance;
		this->ID = nextUniqueID;
		++nextUniqueID;
	}

	int getID() {
		return this->ID;
	}
	double getBalance() {
		return this->balance;
	}
	string getClientName();

	void makeTransaction(Account* alterAccount, double transactionMoney) {
		this->balance -= transactionMoney;
		alterAccount->setMoney(alterAccount->getBalance() + transactionMoney);

		Transaction<tm, int> NewTransactionForMyAccount(alterAccount->getClientName(), alterAccount->getID(), transactionMoney, true);
		Transaction<tm, int> NewTransactionForCounterAccount(alterAccount->getClientName(), this->getID(), transactionMoney, false);

		this->addNewTransaction(NewTransactionForMyAccount);
		alterAccount->addNewTransaction(NewTransactionForCounterAccount);
	}
	void inputNewTransactionFromConsole(Account* alterAccount);

	friend ostream& operator << (ostream& output, const Account& account);

	void showAllTransactionInConsole() {
		cout << "\nAll transaction:" << endl;
		for (Transaction<tm, int> transaction : Transactions)
			cout << transaction << endl;
	}

	vector<Transaction<tm, int>> getAllTransactions() {
		return this->Transactions;
	}
};

int Account::nextUniqueID = 0;