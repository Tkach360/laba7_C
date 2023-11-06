#include <iostream>
#include "Client.h"

using namespace std;

int main() {
	cout << "Class Tests:" << endl;

	int test = 0;

	Client cli("Igor", 23, "234234");
	cout << "\n" << ++test << ") Test constructor with all parameters" << endl; //1
	cli.showInConsole();

	cout << "\n" << ++test << ") Test addAccount" << endl; //2
	cli.addNewAccount(10000);
	cli.Accounts[0].showInConsole();

	cli.addNewAccount(10000);
	cout << "\n" << ++test << ") Test makeTransaction" << endl; //3
	cli.Accounts[0].makeTransaction(&cli.Accounts[1], 5000);
	cli.Accounts[0].showAllTransactionInConsole();
	cli.Accounts[1].showAllTransactionInConsole();

	cout << "\n" << ++test << ") Test addDeposit" << endl; //4
	cli.addNewDeposit(10, 1.08, 100000);
	cli.Deposits[0].showInConsole();

	cout << "\n" << ++test << ") Test addCredit" << endl; //5
	cli.addNewCredit(10, 1.08, 100000, 9000);
	cli.Credits[0].showInConsole();

	cout << "\n" << ++test << ") Test showAllTransactionsInConsole" << endl; //6
	cli.Accounts[0].showAllTransactionInConsole();

	cout << "\n" << ++test << ") Test getFinalContributionsPayments" << endl; //7
	cout << "Final contrib pay: " << cli.Credits[0].getFinalContributionsPayments() << endl;

	cout << "\n" << ++test << ") Test getFinalDepositAmount" << endl; //8
	cout << "Final deposit amount: " << cli.Deposits[0].getFinalDepositAmount() << endl;

	cout << "\n" << ++test << ") Test dynamic" << endl; //9
	Client* cli_d = &cli;
	cli_d->showInConsole();
	cli_d->Accounts[0].makeTransaction(&cli.Accounts[1], 100);
	(*cli_d).addNewCredit(5, 1.05, 10000, 1000);

	cout << "\n" << ++test << ") Test of a dynamic array of class objects " << endl; //10
	Client* cli_arr = new Client[3] { string("Grigory"), string("Victor"), string("Gennadiy") };
	for (int i = 0; i < 3; i++) 
		cout << cli_arr[i].getName() << endl;

	delete[] cli_arr;

	cout << "\n" << ++test << ") Test of an array of dynamic class objects " << endl; //11
	Client* cli_d_arr[3]{ new Client("Guts"), new Client("Griffits"), new Client("Stepan") };
	for (int i = 0; i < 3; i++)
		cout << cli_d_arr[i]->getName() << endl;

	for (int i = 0; i < 3; i++)
		delete cli_d_arr[i];


	cout << "\n" << ++test << ") Test inputClientFromConsole" << endl; //12
	Client cli_c;
	cli_c.inputClientFromConsole();
	cli_c.showInConsole();

	cout << "\n" << ++test << ") Test inputNewAccountFromConsole" << endl; //13
	cli_c.inputNewAccountFromConsole();
	cli_c.Accounts[0].showInConsole();

	cout << "\n" << ++test << ") Test inputNewCreditFromConsole" << endl; //14
	cli_c.inputNewCreditFromConsole();
	cli_c.Credits[0].showInConsole();

	cout << "\n" << ++test << ") Test inputNewDepositFromConsole" << endl; //15
	cli_c.inputNewDepositFromConsole();
	cli_c.Deposits[0].showInConsole();

	cout << "\n" << ++test << ") Test inputNewTransactionFromConsole" << endl; //16
	cli_c.Accounts[0].inputNewTransactionFromConsole(&cli.Accounts[0]);
	cli_c.Accounts[0].showAllTransactionInConsole();
}