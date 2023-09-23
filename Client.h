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
protected:
	bool Sent;
	double Money;
	string CounterClientName;
	int CounterAccountID;
	tm Time;

public:
	Transaction(Account CounterAccount, double Money, bool Sent) {
		this->Sent = Sent;
		this->CounterClientName = CounterAccount.GetClientName();
		this->CounterAccountID = CounterAccount.GetID();
		time_t now = time(NULL);
		this->Time = (*localtime(&now));
	}
};

class Account {
protected:
	int ID;
	double Money;
	std::vector<Transaction> Transactions;

	string ClientName;

public:
	Account();
	Account(int ID, double Money, string ClientName) {
		this->ID = ID;
		this->Money = Money;
		this->ClientName = ClientName;
	}

	int GetID() {
		return this->ID;
	}
	double GetMoney() {
		return this->Money;
	}
	string GetClientName() {
		return this->ClientName;
	}

	void SetMoney(double newMoney) {
		this->Money = newMoney;
	}

	void AddNewTransaction(Transaction newTransaction) {
		this->Transactions.push_back(newTransaction);
	}
	TransactionResult MakeTransaction(Account* CounterAccount, double transactionMoney) {
		this->Money -= transactionMoney;
		CounterAccount->SetMoney(CounterAccount->GetMoney() + transactionMoney);

		Transaction NewTransactionForMyAccount(*CounterAccount, transactionMoney, true);
		Transaction NewTransactionForCounterAccount(*this, -transactionMoney, false);

		this->AddNewTransaction(NewTransactionForMyAccount);
		CounterAccount->AddNewTransaction(NewTransactionForCounterAccount);
	}
};

class BankService {
	//friend void Client::InputNewDepositFromConsole();

protected:
	int Year;
	double Percent; // в формате 1.XX..
	double Body;

public:
	BankService();
	BankService(int Year, double Percent, double Body) {
		this->Year = Year;
		this->Percent = Percent;
		this->Body = Body;
	}

	int GetYear() {
		return this->Year;
	}
	double GetPercent() {
		return this->Percent;
	}
	double GetBody() {
		return this->Body;
	}

	void SetYear(int newYear) {
		this->Year = newYear;
	}
	void SetBody(double newBody) {
		this->Body = newBody;
	}
	void SetPercent(double newPercent) {
		this->Percent = newPercent;
	}
};

class Deposit : public BankService {
public:
	Deposit();
	Deposit(int Year, double Percent, double Body) : BankService(Year, Percent, Body){}
};

class Credit : public BankService {
protected:
	double Contrib;

public:
	Credit();
	Credit(int Year, double Percent, double Body, double Contrib) : BankService(Year, Percent, Body) {
		this->Contrib = Contrib;
	}

	double GetContrib() {
		return this->Contrib;
	}
	void SetContrib(double newContrib) {
		Contrib = newContrib;
	}

	double GetFinalContributionsPayments(Credit credit) {
		double FinalContributionsPayments = 0;
		int years = GetYear();
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
};

class Client {
protected:
	int Age;
	string Name;
	string PhoneNumber;

	vector<Credit> Credits;
	vector<Deposit> Deposits;
	vector<Account> Accounts;

public:
	Client();
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

	void InputClientFromConsole() {
		this->Name = InputClientName("Enter the name of the new client (First Name Last Name): ");
		this->Age = InputInt("Enter the age of the new client: ");
		this->PhoneNumber = InputClientPhoneNumber("Enter the phone number of the new client (X-XXX-XXX-XX-XX): ");

		cout << "Client successfully registered" << endl;
	}

	void AddNewAccount(double money) {
		Account newAccount(Accounts.size(), money, Name);
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
};

//--------------------------------------Deposit------------------------------------------

double GetFinalDepositAmount(Deposit deposit);

//-----------------------------------------------Transaction-------------------------
void InputNewTransactionFromConsole(Account* Account_1, Account* Account_2);