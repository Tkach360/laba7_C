#include <iostream>
#include "Client.h"

using namespace std;

int main() {
	cout << "Class Tests:" << endl;

	int test = 0;

	Client cli("Igor", 23, "234234");
	cout << "\n" << ++test << ") Test constructor with all parameters" << endl;
	cli.ShowInConsole();

	cout << "\n" << ++test << ") Test AddAccount" << endl;
	cli.AddNewAccount(10000);
	cli.Accounts[0].ShowInConsole();

	cli.AddNewAccount(10000);
	cout << "\n" << ++test << ") Test MakeTransaction" << endl;
	cli.Accounts[0].MakeTransaction(&cli.Accounts[1], 5000);
	cli.Accounts[0].ShowAllTransactionInConsole();
	cli.Accounts[1].ShowAllTransactionInConsole();

	cout << "\n" << ++test << ") Test AddDeposit" << endl;
	cli.AddNewDeposit(10, 1.08, 100000);
	cli.Deposits[0].ShowInConsole();

	cout << "\n" << ++test << ") Test AddCredit" << endl;
	cli.AddNewCredit(10, 1.08, 100000, 9000);
	cli.Credits[0].ShowInConsole();

	cout << "\n" << ++test << ") Test ShowAllTransactionsInConsole" << endl;
	cli.Accounts[0].ShowAllTransactionInConsole();

	cout << "\n" << ++test << ") Test GetFinalContributionsPayments" << endl;
	cout << "Final contrib pay: " << cli.Credits[0].GetFinalContributionsPayments() << endl;

	cout << "\n" << ++test << ") Test GetFinalDepositAmount" << endl;
	cout << "Final deposit amount: " << cli.Deposits[0].GetFinalDepositAmount() << endl;

	cout << "\n" << ++test << ") Test dynamic" << endl;
	Client* cli_d = &cli;
	cli_d->ShowInConsole();
	cli_d->Accounts[0].MakeTransaction(&cli.Accounts[1], 100);
	(*cli_d).AddNewCredit(5, 1.05, 10000, 1000);

	cout << "\n" << ++test << ") Test of a dynamic array of class objects " << endl;
	Client* cli_arr = new Client[3] { string("Grigory"), string("Victor"), string("Gennadiy") };
	for (int i = 0; i < 3; i++) 
		cout << cli_arr[i].GetName() << endl;

	cout << "\n" << ++test << ") Test of an array of dynamic class objects " << endl;
	Client* cli_d_arr[3]{ new Client("Guts"), new Client("Griffits"), new Client("Stepan") };
	for (int i = 0; i < 3; i++)
		cout << cli_d_arr[i]->GetName() << endl;



	cout << "\n" << ++test << ") Test InputClientFromConsole" << endl;
	Client cli_c;
	cli_c.InputClientFromConsole();
	cli_c.ShowInConsole();

	cout << "\n" << ++test << ") Test InputNewAccountFromConsole" << endl;
	cli_c.InputNewAccountFromConsole();
	cli_c.Accounts[0].ShowInConsole();

	cout << "\n" << ++test << ") Test InputNewCreditFromConsole" << endl;
	cli_c.InputNewCreditFromConsole();
	cli_c.Credits[0].ShowInConsole();

	cout << "\n" << ++test << ") Test InputNewDepositFromConsole" << endl;
	cli_c.InputNewDepositFromConsole();
	cli_c.Deposits[0].ShowInConsole();

	cout << "\n" << ++test << ") Test InputNewTransactionFromConsole" << endl;
	cli_c.Accounts[0].InputNewTransactionFromConsole(&cli.Accounts[0]);
	cli_c.Accounts[0].ShowAllTransactionInConsole();
}