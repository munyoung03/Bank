#include <iostream>
#include <string>
#define NAME_LEN 20
#define Menu ("-----Menu-----\n1. 계좌개설\n2. 입    금\n3. 출    금\n4. 계좌정보 전체 줄력\n5. 프로그램 종료\n선택: ")
#define MAX_ACCID 100

using namespace std;

class AccountManager
{
private:
	Account* member[MAX_ACCID];
	int memberCount = 0;
public :
	void deposit() {

		int s_accid;
		int money;

		if (memberCount == 0)
		{
			cout << "계좌가 존재하지 않습니다." << endl << endl;
			return;
		}

		cout << "[입   금]" << endl;
		cout << "계좌ID: ";
		cin >> s_accid;

		for (int i = 0; i < memberCount; i++)
		{
			if (member[i]->checkId(s_accid))
			{
				cout << "입금액: ";
				cin >> money;
				if (money <= 0)
				{
					cout << "입금금액은 최소 1원 이상이여야 합니다." << endl << endl;
					return;
				}
				member[i]->deposit(money);
				cout << money << "원 입금되었습니다. 현재 잔액은 " << member[i]->getBalance() << "원입니다." << endl << endl;
				return;
			}
		}
		cout << "유효하지 않은 ID 입니다." << endl;
	}
	

	void withdrawal() {
		if (memberCount == 0)
		{
			cout << "계좌가 존재하지 않습니다." << endl << endl;
			return;
		}

		int s_accid;
		int money;

		cout << "[출   금]" << endl;
		cout << "계좌ID: ";
		cin >> s_accid;

		for (int i = 0; i < memberCount; i++)
		{
			if (member[i]->checkId(s_accid))
			{
				cout << "출금액: ";
				cin >> money;

				if (money <= 0)
				{
					cout << "출금금액은 최소 1원 이상이여야 합니다." << endl << endl;
					return;
				}

				bool check = member[i]->withdrawal(money);

				if (!check)
				{
					cout << "출금 금액이 현재 잔액보다 많습니다." << endl << endl;
					return;
				}

				cout << money << "원 출금되었습니다. 현재 잔액은 " << member[i]->getBalance() << "원입니다." << endl << endl;
				return;
			}
		}
		cout << "유효하지 않은 ID 입니다." << endl;
	}

	void printInfo() {
		if (memberCount == 0)
		{
			cout << "계좌가 존재하지 않습니다." << endl << endl;
			return;
		}

		for (int i = 0; i < memberCount; i++)
		{
			member[i]->printInfo();
		}
	}

	int makeAccid() {

		int accId;
		long long SSN;
		int balance;
		char cusName[NAME_LEN];

		if (memberCount == MAX_ACCID)
		{
			cout << "계좌를 더이상 생성할수 없습니다." << endl << endl;
			return -1;
		}
		cout << "[계좌개설]" << endl;
		cout << "계좌ID: ";
		cin >> accId;
		for (int i = 0; i < memberCount; i++)
		{
			if (member[i]->checkId(accId))
			{
				cout << "동일한 계좌번호가 존재합니다." << endl << endl;
				return -1;
			}
		}
		cout << "주민등록번호: ";
		cin >> SSN;
		for (int i = 0; i < memberCount; i++)
		{
			if (member[i]->checkSSN(SSN))
			{
				cout << "한사람당 계좌는 1개씩만 만들수있습니다." << endl << endl;
				return -1;
			}
		}
		cout << "이  름: ";
		cin >> cusName;
		cout << "입금액: ";
		cin >> balance;
		if (balance < 10)
		{
			cout << "입금액을 10원이상 넣어주세요." << endl << endl;
			return -1;
		}
		cout << "계좌가 성공적으로 개설되었습니다." << endl << endl;

		member[memberCount] = new Account(SSN, accId, balance, cusName);

		memberCount++;
	}
	
	void endProgram() {
		for (int i = 0; i < memberCount; i++)
			delete member[i];
	}
};

class Account
{
private:
	long long SSN; //주민등록번호
	int accID; //계좌번호
	int balance; //잔액
	char* cusName; //고객이름
public:
	Account(long long SSN,int accID,int balance,char* cusName)
		:accID(accID), SSN(SSN), balance(balance)
	{
		this->cusName = new char[NAME_LEN];
		strcpy_s(this->cusName, NAME_LEN, cusName);
	}
	Account(const Account& acc) 
		:accID(acc.accID), SSN(acc.SSN), balance(acc.balance)
	{
		cout << "복사생성자 생성" << endl;
		this->cusName = new char[NAME_LEN];
		strcpy_s(this->cusName, NAME_LEN, acc.cusName);
	}
	~Account() {
		delete[] cusName;
	}

	int getBalance() const
	{
		return balance;
	}

	void deposit(int money) 
	{
		balance += money;
	}

	bool withdrawal(int money)
	{
		if (money > balance) {
			return false;
		}
		balance -= money;
		return true;	
	}

	void printInfo() const{
		cout << "계좌ID: " << accID << endl;
		cout << "이  름: " << cusName << endl;
		cout << "잔  액: " << balance << endl << endl;
	}

	bool checkId(int id) const
	{
		return id == accID;
	}

	bool checkSSN(long long SSN) const
	{
		return SSN == this->SSN;
	}
};

void main() {
	AccountManager accManager;
	int select;
	while (1) {
		cout << Menu;
		cin >> select;
		cout << endl;
		switch (select)
		{
		case 1: accManager.makeAccid();
			break;
		case 2: accManager.deposit();
			break;
		case 3: accManager.withdrawal();
			break;
		case 4: accManager.printInfo();
			break;
		case 5:
			accManager.endProgram();
			return;
		default: "1~5중에 골라주십시오.";
			break;
		}
	}
}