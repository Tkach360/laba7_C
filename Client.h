#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include <vector>
#include <regex>

using namespace std;

bool verifyInt(string ClientAge) {
	regex ClientAgeRegex("\\d+");
	if (regex_match(ClientAge, ClientAgeRegex)) return true;
	else return false;
}
bool verifyDouble(const string& Money) {
	regex MoneyRegex("[0-9]+([.,][0-9]+)?");
	if (regex_match(Money, MoneyRegex)) {
		return true;
	}
	else return false;
}
bool verifyClientName(const string& ClientName) {
	regex ClientNameRegex("^[A-Za-z]*\\s[A-Za-z]*$"); ///////
	cout << regex_match(ClientName, ClientNameRegex) << endl;
	if (regex_match(ClientName, ClientNameRegex)) return true;
	else return false;
}
bool verifyClientPhoneNumber(const string& PhoneNumber) {
	regex PhoneNumberRegex("\\d{1}-\\d{3}-\\d{3}-\\d{2}-\\d{2}");
	if (regex_match(PhoneNumber, PhoneNumberRegex)) return true;
	else return false;
}

int InputInt(string message) {
	string Age;
	do {
		cout << message;
		cin >> Age;
	} while (!verifyInt(Age));
	return stoi(Age);
}
double InputDouble(string message) {
	string Money;
	do {
		cout << message;
		cin >> Money;
	} while (!verifyDouble(Money));
	return stod(Money);
}
string InputClientName(string message) {
	string ClientName;
	do {
		cout << message;
		getline(cin, ClientName);
	} while (!verifyClientName(ClientName));
	return ClientName;
}
string InputClientPhoneNumber(string message) {
	string PhoneNumber;
	do {
		cout << message;
		cin >> PhoneNumber;
	} while (!verifyClientPhoneNumber(PhoneNumber));
	return PhoneNumber;
}

enum TransactionResult {
	InsufficientFunds, // недостаточно средств
	NegativeAmount, // отрицательная сумма
	OK // все ок
};

class Transaction {
protected:
	bool Sent;
	double Money;
	string AlterClientName;
	int AlterAccountID;
	tm Time;

public:
	Transaction(string AlterClientName, int AlterAccountID, double Money, bool Sent) {
		this->Sent = Sent;
		this->AlterAccountID = AlterAccountID;
		this->AlterClientName = AlterClientName;
		this->Money = Money;
		time_t now = time(NULL);
		localtime_s(&this->Time, &now);
	}

	bool GetSent() {
		return this->Sent;
	}
	double GetMoney() {
		return this->Money;
	}
	string GetAlterClientName() {
		return AlterClientName;
	}
	int GetAlterAccountID() {
		return AlterAccountID;
	}
	tm GetTime() {
		return Time;
	}

	void ShowInConsole() {
		string strTime = to_string(Time.tm_mday) + "." + to_string(Time.tm_mon + 1) + "." 
			+ to_string(Time.tm_year + 1900) + " " + to_string(Time.tm_hour) + ":" + to_string(Time.tm_min);
		string strMoney, strAlterClientName, strAlterAccountID;

		if (this->Sent) {
			strMoney = "-" + to_string(this->Money);
			strAlterClientName = "to " + this->AlterClientName;
		}
		else {
			strMoney = "+" + to_string(Money);
			strAlterClientName = "from " + this->AlterClientName;
		}

		strAlterAccountID = to_string(AlterAccountID);
		cout << "Time: " + strTime + " " + strMoney + " " + strAlterClientName + " acc. " + strAlterAccountID << endl;
	}
};

class Account {
	friend class Client;

protected:
	int ID;
	double Balance;

	string ClientName;

	void SetMoney(double newMoney) {
		this->Balance = newMoney;
	}
	void AddNewTransaction(Transaction newTransaction) {
		this->Transactions.push_back(newTransaction);
	}

public:
	vector<Transaction> Transactions;

	Account() {};
	Account(int ID) {
		this->ID = ID;
	}
	Account(double Balance) {
		this->Balance = Balance;
	}
	Account(string ClientName) {
		this->ClientName = ClientName;
	}
	Account(int ID, double Money, string ClientName) {
		this->ID = ID;
		this->Balance = Money;
		this->ClientName = ClientName;
	}

	int GetID() {
		return this->ID;
	}
	double GetBalance() {
		return this->Balance;
	}
	string GetClientName() {
		return this->ClientName;
	}

	void MakeTransaction(Account* AlterAccount, double transactionMoney) {
		this->Balance -= transactionMoney;
		AlterAccount->SetMoney(AlterAccount->GetBalance() + transactionMoney);

		Transaction NewTransactionForMyAccount(AlterAccount->GetClientName(), AlterAccount->GetID(), transactionMoney, true);
		Transaction NewTransactionForCounterAccount(AlterAccount->GetClientName(), this->GetID(), transactionMoney, false);

		this->AddNewTransaction(NewTransactionForMyAccount);
		AlterAccount->AddNewTransaction(NewTransactionForCounterAccount);
	}
	void InputNewTransactionFromConsole(Account* AlterAccount) {
		string message = "Enter the amount you wish to transfer from " + this->ClientName +
			" account number " + to_string(this->GetID()) + " to " + AlterAccount->GetClientName() +
			" account number " + to_string(AlterAccount->GetID()) + ": ";

		double transactionMoney;
		do {
			transactionMoney = InputDouble(message);
			if (transactionMoney == 0) cout << "The transfer amount cannot be zero" << endl;
		} while (transactionMoney == 0);

		MakeTransaction(AlterAccount, transactionMoney);
		cout << "Operation was successfully completed" << endl;
	}
	void ShowInConsole() {
		string Info = "Client: " + this->ClientName + " num: " + to_string(this->ID) +
			" balance: " + to_string(this->Balance);
		cout << Info << endl;
	}
	void ShowAllTransactionInConsole() {
		cout << "All transaction:" << endl;
		for (Transaction transaction : Transactions)
			transaction.ShowInConsole();
	}
	vector<Transaction> GetAllTransactions() {
		return this->Transactions;
	}
};

class BankService {
protected:
	int Year;
	double Percent; // в формате 1.XX..
	double Body;


public:
	BankService() {};
	BankService(int Year) {
		this->Year = Year;
	}
	BankService(double Body) {
		this->Body = Body;
	}
	BankService(int Year, double Percent, double Body) {
		this->Year = Year;
		this->Percent = Percent;
		this->Body = Body;
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

	int GetYear() {
		return this->Year;
	}
	double GetPercent() {
		return this->Percent;
	}
	double GetBody() {
		return this->Body;
	}

};

class Deposit : public BankService {
public:
	Deposit() {};
	Deposit(int Year) : BankService(Year) {};
	Deposit(double Body) : BankService(Body) {};
	Deposit(int Year, double Percent, double Body) : BankService(Year, Percent, Body) {}

	double GetFinalDepositAmount() {
		double FinalDepositAmount = this->GetBody();
		int Year = this->GetYear();
		for (int i = 0; i < Year; i++) {
			FinalDepositAmount *= this->GetPercent();
		}
		return FinalDepositAmount;
	}
	void ShowInConsole() {
		string Info = "Deposit year: " + to_string(this->Year) + " body: " + to_string(this->Body) +
			" percent: " + to_string(this->Percent);
		cout << Info << endl;
	}
};

class Credit : public BankService {
protected:
	double Contrib;

public:
	Credit() {};
	Credit(int Year) : BankService(Year) {};
	Credit(double Body) : BankService(Body) {};
	Credit(int Year, double Percent, double Body, double Contrib) : BankService(Year, Percent, Body) {
		this->Contrib = Contrib;
	}

	void SetContrib(double newContrib) {
		Contrib = newContrib;
	}

	double GetContrib() {
		return this->Contrib;
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
	void ShowInConsole() {
		string Info = "Credit year: " + to_string(this->Year) + " body: " + to_string(this->Body) +
			" percent: " + to_string(this->Percent) + " contribution: " + to_string(this->Contrib);
		cout << Info << endl;
	}
};

class Client {
private:
	int Age;
	string Name;
	string PhoneNumber;

public:
	vector<Credit> Credits;
	vector<Deposit> Deposits;
	vector<Account> Accounts;

	Client(){};
	Client(string Name) {
		this->Name = Name;
	}
	Client(int Age) {
		this->Age = Age;
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

	double GetAllAccountsMoney() {
		double AllAccountsMoney = 0;
		for (Account account : Accounts) {
			AllAccountsMoney += account.GetBalance();
		}
		return AllAccountsMoney;
	}
	void ShowInConsole() {
		cout << "Name: " + this->Name + " Age: " + to_string(this->Age) + " Phone number: " + 
			this->PhoneNumber << endl;
		cout << "  Accounts: " + to_string(this->Accounts.size()) + " Credits: " +
			to_string(this->Credits.size()) + " Deposits: " + to_string(this->Deposits.size()) << endl;
	}
};