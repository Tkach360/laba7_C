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
	} while (!verifyClientPhoneNumber(PhoneNumber));
	return PhoneNumber;
}

class Transaction {
	friend class Account;
protected:
	bool Sent;
	double Money;
	string AlterClientName;
	int AlterAccountID;
	tm Time;

	Transaction(string AlterClientName, int AlterAccountID, double Money, bool Sent) {
		this->Sent = Sent;
		this->AlterAccountID = AlterAccountID;
		this->AlterClientName = AlterClientName;
		this->Money = Money;
		time_t now = time(NULL);
		localtime_s(&this->Time, &now);
	}
	~Transaction() {
		delete& this->Sent, & this->Money, & this->AlterClientName, & this->AlterAccountID, & this->Time;
	}

public:
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

	~Account() {
		delete& ID, & Balance, & ClientName, &Transactions;
	}

	void SetMoney(double newMoney) {
		this->Balance = newMoney;
	}
	void AddNewTransaction(Transaction newTransaction) {
		this->Transactions.push_back(newTransaction);
	}

public:
	vector<Transaction> Transactions;

	Account() {
		this->Balance = 0;
		this->ID = -1;
		this->ClientName = "NONE";
	}
	Account(int ID) {
		this->ID = ID;
		this->Balance = 0;
		this->ClientName = "NONE";
	}
	Account(double Balance) {
		this->Balance = Balance;
		this->ID = -1;
		this->ClientName = "NONE";
	}
	Account(string ClientName) {
		this->Balance = 0;
		this->ID = -1;
		this->ClientName = ClientName;
	}
	Account(int ID, string ClientName) {
		this->ID = ID;
		this->Balance = 0;
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
	friend class Client;
protected:
	int Years;
	double Percent; // в формате 1.XX..
	double Body;

public:
	BankService() {
		this->Years = -1;
		this->Percent = -1;
		this->Body = -1;
	}
	BankService(int Years) {
		this->Years = Years;
		this->Percent = -1;
		this->Body = -1;
	}
	BankService(double Body) {
		this->Body = Body;
		this->Years = -1;
		this->Percent = -1;
	}
	BankService(int Years, double Percent, double Body) {
		this->Years = Years;
		this->Percent = Percent;
		this->Body = Body;
	}

	void SetYear(int newYear) {
		this->Years = newYear;
	}
	void SetBody(double newBody) {
		this->Body = newBody;
	}
	void SetPercent(double newPercent) {
		this->Percent = newPercent;
	}

	int GetYears() {
		return this->Years;
	}
	double GetPercent() {
		return this->Percent;
	}
	double GetBody() {
		return this->Body;
	}

};

class Deposit : public BankService {
	friend class Client;
protected:
	~Deposit() {
		delete& this->Years, & this->Percent, & this->Body;
	}
public:
	Deposit() : BankService() {};
	Deposit(int Years) : BankService(Years) {};
	Deposit(double Body) : BankService(Body) {};
	Deposit(int Years, double Percent, double Body) : BankService(Years, Percent, Body) {}

	double GetFinalDepositAmount() {
		double FinalDepositAmount = this->GetBody();
		int Years = this->GetYears();
		for (int i = 0; i < Years; i++) {
			FinalDepositAmount *= this->GetPercent();
		}
		return FinalDepositAmount;
	}
	void ShowInConsole() {
		string Info = "Deposit year: " + to_string(this->Years) + " body: " + to_string(this->Body) +
			" percent: " + to_string(this->Percent);
		cout << Info << endl;
	}
};

class Credit : public BankService {
	friend class Client;
protected:
	double Contrib;
	~Credit() {
		delete& this->Body, & this->Contrib, & this->Percent, & this->Years;
	}

public:
	Credit() : BankService() {};
	Credit(int Years) : BankService(Years) {};
	Credit(double Body) : BankService(Body) {};
	Credit(int Years, double Percent, double Body, double Contrib) : BankService(Years, Percent, Body) {
		this->Contrib = Contrib;
	}

	void SetContrib(double newContrib) {
		Contrib = newContrib;
	}

	double GetContrib() {
		return this->Contrib;
	}

	double GetFinalContributionsPayments() {
		double FinalContributionsPayments = 0;
		int years = GetYears();
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
		string Info = "Credit year: " + to_string(this->Years) + " body: " + to_string(this->Body) +
			" percent: " + to_string(this->Percent) + " contribution: " + to_string(this->Contrib);
		cout << Info << endl;
	}
	bool CheckThisCredit() {
		if (!(this->Years > 0 && this->Body > this->Contrib && this->Percent > 1)) return false;
		if (this->Body * (this->Percent - 1) >= this->Contrib) return false;

		int TrueYears = 0;
		double Body = this->Body;
		for (TrueYears; Body > 0; TrueYears++)
			Body -= Body * this->Percent;
		if (TrueYears != this->Years) return false;

		return true;
	}
	static bool CheckCredit(Credit credit) {
		if (!(credit.GetYears() > 0 && credit.GetBody() > credit.GetContrib() && credit.GetPercent() > 1)) return false;
		if (credit.GetBody() * (credit.GetPercent() - 1) >= credit.GetContrib()) return false;

		int TrueYears = 0;
		double Body = credit.GetBody();
		for (TrueYears; Body > 0; TrueYears++)
			Body -= Body * credit.GetPercent();
		if (TrueYears != credit.GetYears()) return false;

		return true;
	}
	static bool CheckCredit(int years, double body, double percent, double contribution) {
		if (!(years > 0 && body > contribution && percent > 1)) return false;
		if (body * (percent - 1) >= contribution) return false;

		int TrueYears = 0;
		double Body = body;
		for (TrueYears; Body > 0; TrueYears++)
			Body -= Body * percent;
		if (TrueYears != years) return false;

		return true;
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

	~Client() {
		delete& this->Age, & this->Name, & this->PhoneNumber, & this->Credits, & this->Deposits, & this->Accounts;
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
		for (int i = 0; i < Accounts.size(); i++)
			Accounts[i].ClientName = Name;
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