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

	// тест обработки исключений
	cout << "\n" << ++test << ") Exception handling test" << endl; //6
	cli.addNewCredit(10, 1.08, 100000, 7000);

	cout << "\n" << ++test << ") Test showAllTransactionsInConsole" << endl; //7
	cli.Accounts[0].showAllTransactionInConsole();

	cout << "\n" << ++test << ") Test getFinalContributionsPayments" << endl; //8
	cout << "Final contrib pay: " << cli.Credits[0].getFinalContributionsPayments() << endl;

	cout << "\n" << ++test << ") Test getFinalDepositAmount" << endl; //9
	cout << "Final deposit amount: " << cli.Deposits[0].getFinalDepositAmount() << endl;


	// демонстраци€ работы с одномерным массивом экземпл€ров класса
	cout << "\n" << ++test << ") One-dimensional array test" << endl;
	Client mass1_cli[3];
	mass1_cli[0].setName("Svjatoslav");
	mass1_cli[1].setName("Tihomir");
	mass1_cli[2].setName("Dobrinja");
	for (int i = 0; i < 3; i++) 
		cout << mass1_cli[i].getName() << endl;

	// демонстраци€ работы с двумерным массивом экземпл€ров класса
	cout << "\n" << ++test << ") Two-dimensional array test" << endl;
	Client mass2_cli[2][2];
	for(int i=0;i<2;i++)
		for (int j = 0; j < 2; j++) {
			mass2_cli[i][j].setName("Client[" + to_string(i) + "][" + to_string(j) + "]");
			cout << mass2_cli[i][j].getName() << endl;
		}


	cout << "\n" << ++test << ") Test dynamic" << endl; //10
	Client* cli_d = &cli;
	cout << *cli_d << endl;
	cli_d->Accounts[0].makeTransaction(&cli.Accounts[1], 100);
	(*cli_d).addNewCredit(5, 1.05, 10000, Credit::getRegularContribution(5, 10000, 1.05));

	cout << "\n" << ++test << ") Test of a dynamic array of class objects " << endl; //11
	Client* cli_arr = new Client[3]{ string("Grigory"), string("Victor"), string("Gennadiy") };
	for (int i = 0; i < 3; i++)
		cout << cli_arr[i].getName() << endl;

	delete[] cli_arr;

	cout << "\n" << ++test << ") Test of an array of dynamic class objects " << endl; //12
	Client* cli_d_arr[3]{ new Client("Guts"), new Client("Griffits"), new Client("Stepan") };
	for (int i = 0; i < 3; i++)
		cout << cli_d_arr[i]->getName() << endl;

	for (int i = 0; i < 3; i++)
		delete cli_d_arr[i];

	cout << "\n" << ++test << ") Test static method Credit::setMaxCreditAmout(50000) " << endl;
	Credit::setMaxCreditAmout(50000);
	cout << "\n" << ++test << ") Test static method Credit::isValidCredit(10, 100000, 1.2, 21000), should be false because maxCreditAmout was exceeded " << endl;
	cout << "    " << Credit::isValidCredit(10, 100000, 1.2, 21000);
	cout << "\n" << ++test << ") Test static method Credit::isValidCredit(10, 10000, 1.2, 1000), should be false because the annual fee is less than a percentage " << endl;
	cout << "    " << Credit::isValidCredit(10, 10000, 1.2, 1000);
	cout << "\n" << ++test << ") Test static method Credit::getRegularContribution(10, 10000, 1.2), should be 2385.23 " << endl;
	cout << "    " << Credit::getRegularContribution(10, 10000, 1.2);
	cout << "    " << Credit::getRegularContribution(20, 20000, 1.2);
	cout << "\n" << ++test << ") Test static method Credit::isValidCredit(10, 10000, 1.2, 2385.23), should be true " << endl;
	cout << "    " << Credit::isValidCredit(10, 10000, 1.2, 2385.23) << endl;

	cout << "\n" << ++test << ") Test static field Account::nextUniqueID " << endl;
	cli.addNewAccount(20000);
	cout << "new Account ID: " << cli.Accounts.back().getID() << endl;
	cli.addNewAccount(20000);
	cout << "new Account ID: " << cli.Accounts.back().getID() << endl;

	// демонстраци€ возврата значени€ через ссылку
	cout << "\n" << ++test << ") Test for returning a value by reference (Client::getAllAccounts())";
	vector<Account> cli_accounts = cli.getAllAccounts();
	cli_accounts[0].showAllTransactionInConsole();

	//демонстраци€ возврата значени€ через указатель
	cout << "\n" << ++test << ") Test for returning a value via a pointer (Client::getAccountByID())" << endl;
	Account* cli_acc = cli.getAccountByID(0);

	// демонстраци€ оператора + дл€ Credit
	cout << "\n" << ++test << ") Test operator overload test + for Credit" << endl;
	Credit first(10, 1.2, 10000, 2385.23);
	cout << first + first << endl;

	// демонстраци€ оператора ++ (префиксна€ форма) дл€ Credit
	cout << "\n" << ++test << ") Test operator overload test ++ (prefix form) for Credit" << endl;
	Credit second(10, 1.2, 10000, 2385.23);
	++second;
	cout << second << endl;

	// демонстраци€ оператора ++ (постфиксна€ форма) дл€ Credit
	cout << "\n" << ++test << ") Test operator overload test ++ (postfix form) for Credit" << endl;
	Credit tree(10, 1.2, 10000, 2385.23);
	tree++;
	cout << tree << endl;

	cout << "\n" << ++test << ") Test inputClientFromConsole" << endl; //12
	Client cli_c;
	cin >> cli_c;
	cout << cli_c << endl;

	cout << "\n" << ++test << ") Test inputNewAccountFromConsole" << endl; //13
	cli_c.inputNewAccountFromConsole();
	cout << cli_c.Accounts[0] << endl;

	cout << "\n" << ++test << ") Test inputNewCreditFromConsole" << endl; //14
	cli_c.inputNewCreditFromConsole();
	cout << cli_c.Credits[0] << endl;

	cout << "\n" << ++test << ") Test inputNewDepositFromConsole" << endl; //15
	cli_c.inputNewDepositFromConsole();
	cout << cli_c.Deposits[0] << endl;

	cout << "\n" << ++test << ") Test inputNewTransactionFromConsole" << endl; //16
	cli_c.Accounts[0].inputNewTransactionFromConsole(&cli.Accounts[0]);
	cli_c.Accounts[0].showAllTransactionInConsole();
}