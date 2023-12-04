#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include "Account.h"
#include "Deposit.h"
#include "Credit.h"

using namespace std;

class Client {

	//разумное использование дружественных функции
	friend void BankService::setYear(int newYear);
	friend void BankService::setBody(double newBody);
	friend void BankService::setPercent(double newPercent);

	friend void Credit::setContrib(double newContrib);

private:
	int age;
	string name;
	string phoneNumber;

	// использование блока инициализации исключения throw
	void checkNewCredit(int Year, double Percent, double Body, double Contrib) {
		if (!Credit::isValidCredit(Year, Body, Percent, Contrib)) {
			throw "Incorrect credit details.";
		}
	}

public:
	vector<Credit> Credits;
	vector<Deposit> Deposits;
	vector<Account> Accounts;

	vector<BankService> BankServices; // контейнер с объектами BankService (может хранить производные классы Deposit и Credit)

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

	// алгоритм поиска
	Account* getAccountByID(int searchID) {
		for (int i = 0; i < Accounts.size(); i++) {
			if (Accounts[i].getID() == searchID)
				return &Accounts[i];
		}
		return nullptr;
	}

	void setPhoneNumber(string phoneNumber) {
		this->phoneNumber = phoneNumber;
	}
	void setAge(int age) {
		this->age = age;
	}
	void setName(string name) {
		this->name = name;
	}

	friend ostream& operator << (ostream& output, const Client& client) {
		output << "Name: " + client.name + " age: " + to_string(client.age) + " Phone number: " +
			client.phoneNumber << endl;
		output << "  Accounts: " + to_string(client.Accounts.size()) + " Credits: " +
			to_string(client.Credits.size()) + " Deposits: " + to_string(client.Deposits.size()) << endl;

		return output;
	}
	friend istream& operator >> (istream& input, Client& client) {
		client.name = inputClientName("Enter the name of the new client (First name Last name): ");
		client.age = inputInt("Enter the age of the new client: ");
		client.phoneNumber = inputClientPhoneNumber("Enter the phone number of the new client (X-XXX-XXX-XX-XX): ");

		cout << "Client successfully registered" << endl;

		return input;
	}

	// разумное использование оператора this
	void addNewAccount(double money) {
		Account newAccount(this, money);
		this->Accounts.push_back(newAccount);
	}
	void inputNewAccountFromConsole() {
		double money = inputDouble("Enter the initial amount in the account: ");

		addNewAccount(money);
		cout << "Account created successfully" << endl;
	}

	// алгоритм сортировки массива Client по возрасту
	void sortedAccountsByBalance() {
		int size = Accounts.size();
		for (int i = 0; i < size - 1; i++) {
			for (int j = i + 1; j < size; j++) {
				if (Accounts[i].getBalance() > Accounts[j].getBalance()) {
					Account bufer = Accounts[i];
					Accounts[i] = Accounts[j];
					Accounts[j] = bufer;
				}
			}
		}
	}

	// использование блоков try-catch
	void addNewCredit(int Year, double Percent, double Body, double Contrib) {
		try {
			checkNewCredit(Year, Percent, Body, Contrib);
			Credit newCredit(Year, Percent, Body, Contrib);
			this->Credits.push_back(newCredit);
		}
		catch(const char* msg) {
			cout << msg << endl;
		}
	}

	// использование блоков try-catch
	void addNewCredit(Credit newCredit) {
		try {
			checkNewCredit(newCredit.getYears(), newCredit.getPercent(), newCredit.getBody(), newCredit.getContrib());
			this->Credits.push_back(newCredit);
		}
		catch (const char* msg) {
			cout << msg << endl;
		}
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


	vector<Transaction<tm, int>> getAllTransactions() {
		vector<Transaction<tm, int>> AllTransactions;
		for (Account account : Accounts)
			AllTransactions.insert(AllTransactions.end(), account.Transactions.begin(), account.Transactions.end());
		return AllTransactions;
	}

	// методы возврата значений через ссылки
	vector<Account>& getAllAccounts() {
		return this->Accounts;
	}
	vector<Deposit>& getAllDeposits() {
		return this->Deposits;
	}
	vector<Credit>& getAllCredits() {
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

ostream& operator << (ostream& output, const Account& account) {
	string Info = "Client: " + account.client->getName() + " num: " + to_string(account.ID) +
		" balance: " + to_string(account.balance);
	cout << Info << endl;

	return output;
}