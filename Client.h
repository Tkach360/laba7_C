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
	double Money;
	string RecipientClientName;
	string SenderClientName;
	int RecipientAccountID;
	int SenderAccountID;
	tm Time;

public:
	Transaction(string recipientClientName, string senderClientName, double money, 
		int recipientAccountID, int senderAccountID) {

		RecipientClientName = recipientClientName;
		SenderClientName = senderClientName;
		RecipientAccountID = recipientAccountID;
		SenderAccountID = senderAccountID;
		time_t now = time(NULL);
		Time = (*localtime(&now));
	}
};

class Account {
protected:
	int ID;
	double Money;
	std::vector<Transaction> Transactions;

	string ClientName; // нужно чтобы при использовании NewTransaction не передавать ещё и имя

public:
	Account();
	Account(int id, double money) {
		ID = id;
		Money = money;
	}

	int GetID() {
		return ID;
	}
	double GetMoney() {
		return Money;
	}

	void SetMoney(double newMoney) {
		Money = newMoney;
	}
};

class BankService {
	friend void Client::InputNewDepositFromConsole();

protected:
	int Year;
	double Percent; // в формате 1.XX..
	double Body;

public:
	BankService();
	BankService(int year, double percent, double body) {
		Year = year;
		Percent = percent;
		Body = body;
	}

	int GetYear() {
		return Year;
	}
	double GetPercent() {
		return Percent;
	}
	double GetBody() {
		return Body;
	}

	void SetYear(int newYear) {
		Year = newYear;
	}
	void SetBody(double newBody) {
		Body = newBody;
	}
	void SetPercent(double newPercent) {
		Percent = newPercent;
	}
};

class Deposit : public BankService {
public:
	Deposit();
	Deposit(int year, double percent, double body) : BankService(year, percent, body){}
};

class Credit : public BankService {
protected:
	double Contrib;

public:
	Credit();
	Credit(int year, double percent, double body, double contrib) : BankService(year, percent, body) {
		Contrib = contrib;
	}

	double GetContrib() {
		return Contribution;
	}
	void SetContrib(double newContrib) {
		Contrib = newContrib;
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
		Name = InputClientName("Enter the name of the new client (First Name Last Name): ");
		Age = InputInt("Enter the age of the new client: ");
		PhoneNumber = InputClientPhoneNumber("Enter the phone number of the new client (X-XXX-XXX-XX-XX): ");

		cout << "Client successfully registered" << endl;
	}

	void AddNewAccount(double money) {
		Account newAccount(Accounts.size(), money);
		Accounts.push_back(newAccount);
	}
	void InputNewAccountFromConsole() {
		double money = InputDouble("Enter the initial amount in the account: ");

		AddNewAccount(money);
		cout << "Account created successfully" << endl;
	}

	void AddNewTransaction(Account *MyAccount, Account *AnotherAccount, double transactionMoney) {
		MyAccount->SetMoney(MyAccount->GetMoney() - transactionMoney);
		AnotherAccount->SetMoney(MyAccount->GetMoney() + transactionMoney);

		Transaction 

		MyAccount->Transactions.push_back(newTransactionForAccount_1);
		AnotherAccount->Transactions.push_back(newTransactionForAccount_2);
	}

	void AddNewCredit(int Year, double Percent, double Body, double Contrib) {
		Credit newCredit(Year, Percent, Body, Contrib);
		Credits.push_back(newCredit);
	}
	void AddNewCredit(Credit newCredit) {
		Credits.push_back(newCredit);
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
		Deposits.push_back(newDeposit);
	}
	void AddNewDeposit(Deposit newDeposit) {
		Deposits.push_back(newDeposit);
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

//---------------------------------------Account--------------------------------------

int GetAccountId(Account account);
double GetMoney(Account account);

//-------------------------------------Credit-----------------------------------------

double GetFinalContributionsPayments(Credit credit);

//--------------------------------------Deposit------------------------------------------

double GetFinalDepositAmount(Deposit deposit);

//-----------------------------------------------Transaction-------------------------

TransactionResult NewTransaction(Account* Account_1, Account* Account_2, double transactionMoney);
void InputNewTransactionFromConsole(Account* Account_1, Account* Account_2);