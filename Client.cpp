#define _CRT_SECURE_NO_WARNINGS

#include "Client.h"
#include <regex>

using namespace std;

//------------------------------------------Input-Int-Double---------------------------------

bool verifyInt(const string& ClientAge) {
	regex ClientAgeRegex("\\d+");
	if (regex_match(ClientAge, ClientAgeRegex)) return true;
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

bool verifyDouble(const string& Money) {
	regex MoneyRegex("[0-9]+([.,][0-9]+)?");
	if (regex_match(Money, MoneyRegex)) {
		return true;
	}
	else return false;
}

double InputDouble(string message) {
	string Money;
	do {
		cout << message;
		cin >> Money;
	} while (!verifyDouble(Money));
	return stod(Money);
}

//------------------------------------------------Client------------------------------------------

//double GetAllAccountsMoney(Client client) {
//	double AllAccountsMoney = 0;
//	for (Account account : client.Accounts)
//	{
//		AllAccountsMoney += account.money;
//	}
//	return AllAccountsMoney;
//}

//---------------------------------InputClientFromConsole------------------------------------

bool verifyClientName(const string& ClientName) {
	regex ClientNameRegex("^[A-Za-z]*\\s[A-Za-z]*$"); ///////
	cout << regex_match(ClientName, ClientNameRegex) << endl;
	if (regex_match(ClientName, ClientNameRegex)) return true;
	else return false;
}

string InputClientName(string message) {
	string ClientName;
	do {
		cout << message;
		getline(cin, ClientName);
	} while (!verifyClientName(ClientName));
	return ClientName;
}

bool verifyClientPhoneNumber(const string& PhoneNumber) {
	regex PhoneNumberRegex("\\d{1}-\\d{3}-\\d{3}-\\d{2}-\\d{2}");
	if (regex_match(PhoneNumber, PhoneNumberRegex)) return true;
	else return false;
}

string InputClientPhoneNumber(string message) {
	string PhoneNumber;
	do {
		cout << message;
		cin >> PhoneNumber;
	} while (!verifyClientPhoneNumber(PhoneNumber));
	return PhoneNumber;
}

//-------------------------------------Credit-----------------------------------------------------

//double GetContribution(Credit credit) { return credit.contribution; }
//double GetFinalContributionsPayments(Credit credit) {
//	double FinalContributionsPayments = 0;
//	int years = GetYear(credit);
//	double body = GetBody(credit);
//	double percent = GetPercent(credit);
//	double contribution = GetContribution(credit);
//	for (int i = 0; i < years; i++) {
//		if (body < contribution) {
//			FinalContributionsPayments += body;
//			body = 0;
//		}
//		else {
//			FinalContributionsPayments += contribution;
//			body -= contribution;
//			body *= percent;
//		}
//	}
//	return FinalContributionsPayments;
//}
//

//------------------------------------------NewTransaction--------------------------------------------

//Transaction InitTransaction(Account account, string CounterName, double money) {
//	Transaction newTransaction;
//	newTransaction.money = money;
//	newTransaction.CounterName = CounterName;
//	newTransaction.CounterAccountId = GetAccountId(account);
//
//	time_t now = time(NULL);
//	newTransaction.Time = (*localtime(&now));
//
//	return newTransaction;
//}

//TransactionResult NewTransaction(Account* Account_1, Account* Account_2, double transactionMoney) {
//	if (Account_1->money - transactionMoney < 0) { // проверка, достаточно ли средств
//		return InsufficientFunds;
//	}
//	if (transactionMoney <= 0) { // проверка на перевод отрицательной или нулевой суммы
//		return NegativeAmount;
//	}
//
//	Account_1->money -= transactionMoney;
//	Account_2->money += transactionMoney;
//
//	Transaction newTransactionForAccount_1 = InitTransaction(*Account_2, Account_1->ClientName, transactionMoney);
//	Transaction newTransactionForAccount_2 = InitTransaction(*Account_1, Account_2->ClientName, -transactionMoney);
//
//	Account_1->Transactions.push_back(newTransactionForAccount_1);
//	Account_2->Transactions.push_back(newTransactionForAccount_2);
//
//	return OK;
//}
//
////-------------------------------------InputTransactionFromConsole------------------------------------

//void InputNewTransactionFromConsole(Account* Account_1, Account* Account_2) {
//	string message = "Enter the amount you wish to transfer from " + Account_1->ClientName +
//		" account number " + to_string(Account_1->id) + " to " + Account_2->ClientName +
//		" account number " + to_string(Account_2->id) + ": ";
//
//	double transactionMoney;
//	do {
//		transactionMoney = InputDouble(message);
//		if (transactionMoney == 0) cout << "The transfer amount cannot be zero" << endl;
//	} while (transactionMoney == 0);
//
//	NewTransaction(Account_1, Account_2, transactionMoney);
//	cout << "Operation was successfully completed" << endl;
//}