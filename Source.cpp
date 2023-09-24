#include <iostream>
#include "Client.h"

int main() {
	Client cli;
	cli.AddNewAccount(10000);
	cout << cli.Accounts[0].GetID();
}