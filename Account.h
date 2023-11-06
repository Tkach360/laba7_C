#pragma once

#include "Client.h"
#include "Transaction.h"

using namespace std;

class Account {
	friend class Client;

private:
	int ID;
	double Balance;

	Client* client;


	void SetMoney(double newMoney) {
		this->Balance = newMoney;
	}
	void AddNewTransaction(Transaction newTransaction) {
		this->Transactions.push_back(newTransaction);
	}

public:
	vector<Transaction> Transactions;

	Account(Client* client) {
		this->client = client;
		this->Balance = 0;
		this->ID = -1;
	}
	Account(Client* client, int ID) {
		this->client = client;
		this->ID = ID;
		this->Balance = 0;
	}
	Account(Client* client, double Balance) {
		this->client = client;
		this->Balance = Balance;
		this->ID = -1;
	}
	Account(Client* client, int ID, double Money) {
		this->client = client;
		this->ID = ID;
		this->Balance = Money;
	}

	int GetID() {
		return this->ID;
	}
	double GetBalance() {
		return this->Balance;
	}
	string GetClientName();

	void MakeTransaction(Account* AlterAccount, double transactionMoney) {
		this->Balance -= transactionMoney;
		AlterAccount->SetMoney(AlterAccount->GetBalance() + transactionMoney);

		Transaction NewTransactionForMyAccount(AlterAccount->GetClientName(), AlterAccount->GetID(), transactionMoney, true);
		Transaction NewTransactionForCounterAccount(AlterAccount->GetClientName(), this->GetID(), transactionMoney, false);

		this->AddNewTransaction(NewTransactionForMyAccount);
		AlterAccount->AddNewTransaction(NewTransactionForCounterAccount);
	}
	void InputNewTransactionFromConsole(Account* AlterAccount);

	void ShowInConsole();

	void ShowAllTransactionInConsole() {
		cout << "All transaction:" << endl;
		for (Transaction transaction : Transactions)
			transaction.ShowInConsole();
	}

	vector<Transaction> GetAllTransactions() {
		return this->Transactions;
	}
};