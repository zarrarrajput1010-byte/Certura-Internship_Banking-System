#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Account {
private:
	string name;
	int accNo;
	double balance;
	
public:
	Account() {}
	Account(string n, int a, double b) : name(n), accNo(a), balance(b) {}
	
	void deposit(double amt) { balance += amt; }
	bool withdraw(double amt) {
		if (amt > balance) return false;
		balance -= amt;
		return true;
	}
	double getBalance() const { return balance; }
	int getAccNo() const { return accNo; }
	string getName() const { return name; }
	void display() const {
		cout << "Name: " << name << ", Acc No: " << accNo << ", Balance: " << balance << endl;
	}
};

vector<Account> accounts;
const string filename = "accounts.txt";

void loadAccounts() {
	ifstream file(filename);
	if (!file) return;
	
	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		string name;
		int accNo;
		double balance;
		if (getline(ss, name, ',') && (ss >> accNo) && (ss.ignore(), ss >> balance)) {
			accounts.push_back(Account(name, accNo, balance));
		}
	}
	file.close();
}

void saveAccounts() {
	ofstream file(filename);
	for (const auto& acc : accounts) {
		file << acc.getName() << "," << acc.getAccNo() << "," << acc.getBalance() << endl;
	}
	file.close();
}

int findAccount(int accNo) {
	for (size_t i = 0; i < accounts.size(); ++i) {
		if (accounts[i].getAccNo() == accNo) return static_cast<int>(i);
	}
	return -1;
}

void createAccount() {
	string name;
	int accNo;
	double balance;
	cout << "Enter name: ";
	cin.ignore();
	getline(cin, name);
	cout << "Enter account number: ";
	cin >> accNo;
	cout << "Enter Initial balance: ";
	cin >> balance;
	accounts.push_back(Account(name, accNo, balance));
	saveAccounts();
	cout << "Accounts created." << endl;
}

void deposit() {
	int accNo;
	double amt;
	cout << "Enter account number: ";
	cin >> accNo;
	int idx = findAccount(accNo);
	if (idx == -1) {
		cout << "Account not found." << endl;
		return;
	}
	cout << "Enter amount to deposit: ";
	cin >> amt;
	accounts[idx].deposit(amt);
	saveAccounts();
	cout << "Amounts deposited." << endl;
}

void withdraw() {
	int accNo;
	double amt;
	cout << "Enter account number: ";
	cin >> accNo;
	int idx = findAccount(accNo);
	if (idx == -1) {
		cout << "Account not found." << endl;
		return;
	}
	cout << "Enter amount to withdraw: ";
	cin >> amt;
	if (accounts[idx].withdraw(amt)) {
		saveAccounts();
		cout << "Amount withdrawn." << endl;
	}
	else {
		cout << "Insufficient balance." << endl;
	}
}

void balanceInquiry() {
	int accNo;
	cout << "Enter account number: ";
	cin >> accNo;
	int idx = findAccount(accNo);
	if (idx == -1) {
		cout << "Account not found." << endl;
		return;
	}
	cout << "Balance: " << accounts[idx].getBalance() << endl;
}

int main() {
	loadAccounts();
	int choice;
	do {
		cout << "\nBanking System Menu:\n";
		cout << "1. Create Account\n";
		cout << "2. Deposit\n";
		cout << "3. Withdraw\n";
		cout << "4. Balance Inquiry\n";
		cout << "5. Exit\n";
		cout << "Enter choice: ";
		cin >> choice;
		switch (choice) {
			case 1:
				createAccount();
				break;
			case 2:
				deposit();
				break;
			case 3:
				withdraw();
				break;
			case 4:
				balanceInquiry();
				break;
			case 5:
				cout << "Exiting..." << endl;
				break;
			default:
				cout << "Invalid choice." << endl;
		}
	}
	while (choice != 5);
	return 0;
}