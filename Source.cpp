#include <iostream>
#include "Client.h"

using namespace std;

int main() {
	cout << "Class Tests:" << endl;

	int test = 0;

	Client cli("Igor", 23, "234234");
	cout << "\n" << ++test << ") Test constructor with all parameters" << endl; //1
	cout << cli << endl;

	cout << "\n" << ++test << ") Test addAccount" << endl; //2
	cli.addNewAccount(10000);
	cout << cli.Accounts[0] << endl;

	cli.addNewAccount(10000);
	cout << "\n" << ++test << ") Test makeTransaction" << endl; //3
	cli.Accounts[0].makeTransaction(&cli.Accounts[1], 5000);
	cli.Accounts[0].showAllTransactionInConsole();
	cli.Accounts[1].showAllTransactionInConsole();

	cout << "\n" << ++test << ") Test addDeposit" << endl; //4
	cli.addNewDeposit(10, 1.08, 100000);
	cout << cli.Deposits[0] << endl;

	cout << "\n" << ++test << ") Test addNewCredit" << endl; //5
	cli.addNewCredit(10, 1.08, 100000, Credit::getRegularContribution(10, 100000, 1.08));
	cout << cli.Credits[0] << endl;

	cout << "\n" << ++test << ") Test getInterestAmount" << endl;
	cout << cli.Credits[0].getInterestAmount() << endl;

	// демонстрация перегрузки метода в производном классе
	cout << "\n" << ++test << ") Test setNewData" << endl;
	cli.Credits[0].setNewData(5, 1.05, 10000, Credit::getRegularContribution(5, 10000, 1.05));
	cout << cli.Credits[0] << endl;

	// демонстрация перегрузки оператора присваивания
	cout << "\n" << ++test << ") Assignment test an object of a derived class of objects of a base class" << endl;
	BankService* bs = new BankService(10, 1.04, 50000);
	cli.Credits[0] = *bs;
	cout << cli.Credits[0] << endl;

	// демонстрация работы виртуальной функции
	cout << "\n" << ++test << ") Test virual function" << endl;
	bs->applyPenalty(0.02);
	cli.Credits[0].applyPenalty(0.02);
}