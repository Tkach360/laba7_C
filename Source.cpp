#include <iostream>
#include "Client.h"

int main() {

	Client cli("Robert", 29, "8-964-876-99-88");
	cli.AddNewAccount(10000);
	cli.AddNewAccount(2000);
	cli.Accounts[0].MakeTransaction(&cli.Accounts[1], 2000);

	cli.Accounts[1].Transactions[0].ShowInConsole();
	cli.Accounts[0].Transactions[0].ShowInConsole();
}