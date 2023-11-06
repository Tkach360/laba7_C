#include <iostream>
#include "Client.h"

using namespace std;

int main() {
	cout << "Class Tests:" << endl;

	int test = 0;

	Client cli("Igor", 23, "234234");
	cout << "\n" << ++test << ") Test constructor with all parameters" << endl; //1
	cli.ShowInConsole();

	cout << "\n" << ++test << ") Test AddAccount" << endl; //2
	cli.AddNewAccount(10000);
	cli.Accounts[0].ShowInConsole();

	cli.AddNewAccount(10000);
	cout << "\n" << ++test << ") Test MakeTransaction" << endl; //3
	cli.Accounts[0].MakeTransaction(&cli.Accounts[1], 5000);
	cli.Accounts[0].ShowAllTransactionInConsole();
	cli.Accounts[1].ShowAllTransactionInConsole();

	cout << "\n" << ++test << ") Test AddDeposit" << endl; //4
	cli.AddNewDeposit(10, 1.08, 100000);
	cli.Deposits[0].ShowInConsole();

	cout << "\n" << ++test << ") Test AddCredit" << endl; //5
	cli.AddNewCredit(10, 1.08, 100000, 9000);
	cli.Credits[0].ShowInConsole();

	cout << "\n" << ++test << ") Test ShowAllTransactionsInConsole" << endl; //6
	cli.Accounts[0].ShowAllTransactionInConsole();

	cout << "\n" << ++test << ") Test GetFinalContributionsPayments" << endl; //7
	cout << "Final contrib pay: " << cli.Credits[0].GetFinalContributionsPayments() << endl;

	cout << "\n" << ++test << ") Test GetFinalDepositAmount" << endl; //8
	cout << "Final deposit amount: " << cli.Deposits[0].GetFinalDepositAmount() << endl;

	cout << "\n" << ++test << ") Test dynamic" << endl; //9
	Client* cli_d = &cli;
	cli_d->ShowInConsole();
	cli_d->Accounts[0].MakeTransaction(&cli.Accounts[1], 100);
	(*cli_d).AddNewCredit(5, 1.05, 10000, 1000);

	cout << "\n" << ++test << ") Test of a dynamic array of class objects " << endl; //10
	Client* cli_arr = new Client[3] { string("Grigory"), string("Victor"), string("Gennadiy") };
	for (int i = 0; i < 3; i++) 
		cout << cli_arr[i].GetName() << endl;

	delete[] cli_arr;

	cout << "\n" << ++test << ") Test of an array of dynamic class objects " << endl; //11
	Client* cli_d_arr[3]{ new Client("Guts"), new Client("Griffits"), new Client("Stepan") };
	for (int i = 0; i < 3; i++)
		cout << cli_d_arr[i]->GetName() << endl;

	for (int i = 0; i < 3; i++)
		delete cli_d_arr[i];


	cout << "\n" << ++test << ") Test InputClientFromConsole" << endl; //12
	Client cli_c;
	cli_c.InputClientFromConsole();
	cli_c.ShowInConsole();

	cout << "\n" << ++test << ") Test InputNewAccountFromConsole" << endl; //13
	cli_c.InputNewAccountFromConsole();
	cli_c.Accounts[0].ShowInConsole();

	cout << "\n" << ++test << ") Test InputNewCreditFromConsole" << endl; //14
	cli_c.InputNewCreditFromConsole();
	cli_c.Credits[0].ShowInConsole();

	cout << "\n" << ++test << ") Test InputNewDepositFromConsole" << endl; //15
	cli_c.InputNewDepositFromConsole();
	cli_c.Deposits[0].ShowInConsole();

	cout << "\n" << ++test << ") Test InputNewTransactionFromConsole" << endl; //16
	cli_c.Accounts[0].InputNewTransactionFromConsole(&cli.Accounts[0]);
	cli_c.Accounts[0].ShowAllTransactionInConsole();
}