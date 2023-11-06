#pragma once

#include <regex>
#include <iostream>

using namespace std;

bool verifyInt(string ClientAge) {
	regex ClientAgeRegex("\\d+");
	if (regex_match(ClientAge, ClientAgeRegex)) return true;
	else return false;
}
bool verifyDouble(const string& Money) {
	regex MoneyRegex("[0-9]+([.,][0-9]+)?");
	if (regex_match(Money, MoneyRegex)) {
		return true;
	}
	else return false;
}
bool verifyClientName(const string& ClientName) {
	regex ClientNameRegex("^[A-Za-z]*\\s[A-Za-z]*$"); ///////
	if (regex_match(ClientName, ClientNameRegex)) return true;
	else return false;
}
bool verifyClientPhoneNumber(const string& PhoneNumber) {
	regex PhoneNumberRegex("\\d{1}-\\d{3}-\\d{3}-\\d{2}-\\d{2}");
	if (regex_match(PhoneNumber, PhoneNumberRegex)) return true;
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
double InputDouble(string message) {
	string Money;
	do {
		cout << message;
		cin >> Money;
	} while (!verifyDouble(Money));
	return stod(Money);
}
string InputClientName(string message) {
	string ClientName;
	do {
		cout << message;
		getline(cin, ClientName);
	} while (!verifyClientName(ClientName));
	return ClientName;
}
string InputClientPhoneNumber(string message) {
	string PhoneNumber;
	do {
		cout << message;
		cin >> PhoneNumber;
	} while (!verifyClientPhoneNumber(PhoneNumber));
	return PhoneNumber;
}