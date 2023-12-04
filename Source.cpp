#include <iostream>
#include "Client.h"

using namespace std;

int main() {
	cout << "Class Tests:" << endl;

	int test = 0;

	Client cli("Igor", 23, "234234");
	cout << "\n" << ++test << ") Test sortedAccountsByBalance" << endl; //1
	for (int i = 5; i > 0; i--)
		cli.addNewAccount(i * 1000);

	cout << "Before sorted:" << endl;
	for (int i = 0; i < cli.Accounts.size(); i++)
		cout << cli.Accounts[i];

	cli.sortedAccountsByBalance();

	cout << "After sorted:" << endl;
	for (int i = 0; i < cli.Accounts.size(); i++)
		cout << cli.Accounts[i];
	
	cout << "\n" << ++test << ") Test getAccountByID" << endl; //2
	cout << *cli.getAccountByID(1);
	
}