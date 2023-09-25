#include <iostream>
#include "Client.h"

int main() {
	cout << "Class Tests:" << endl;

	Client cli("Igor", 23, "234234");
	cout << "\n1) Test constructor with all parameters" << endl;
	cli.ShowInConsole();

	cout << "\n2) Test AddAccount" << endl;
	cli.AddNewAccount(10000);
	cli.Accounts[0].ShowInConsole();

	cli.AddNewAccount(10000);
	cout << "\n3) Test MakeTransaction" << endl;
	cli.Accounts[0].MakeTransaction(&cli.Accounts[1], 5000);
	cli.Accounts[0].ShowAllTransactionInConsole();
	cli.Accounts[1].ShowAllTransactionInConsole();

	cout << "\n4) Test AddDeposit" << endl;
	cli.AddNewDeposit(10, 1.08, 100000);
	cli.Deposits[0].ShowInConsole();

	cout << "\n5) Test AddCredit" << endl;
	cli.AddNewCredit(10, 1.08, 100000, 9000);
	cli.Credits[0].ShowInConsole();

	cout << "\n6) Test ShowAllTransactionsInConsole" << endl;
	cli.Accounts[0].ShowAllTransactionInConsole();

	cout << "\n7) Test GetFinalContributionsPayments" << endl;
	cli.Credits[0].GetFinalContributionsPayments();

	cout << "\n8) Test GetFinalDepositAmount" << endl;
	cli.Deposits[0].GetFinalDepositAmount();

	cout << "\n9) Test InputClientFromConsole" << endl;
	Client cli_c;
	cli_c.InputClientFromConsole();
	cli_c.ShowInConsole();

	cout << "\n10) Test InputNewAccountFromConsole" << endl;
	cli_c.InputNewAccountFromConsole();
	cli_c.Accounts[0].ShowInConsole();

	cout << "\n11) Test InputNewCreditFromConsole" << endl;
	cli_c.InputNewCreditFromConsole();
	cli_c.Credits[0].ShowInConsole();

	cout << "\n12) Test InputNewDepositFromConsole" << endl;
	cli_c.InputNewDepositFromConsole();
	cli_c.Deposits[0].ShowInConsole();

	cout << "\n13) Test InputNewTransactionFromConsole" << endl;
	cli_c.Accounts[0].InputNewTransactionFromConsole(&cli.Accounts[0]);
	cli_c.Accounts[0].ShowAllTransactionInConsole();
}