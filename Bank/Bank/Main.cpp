#include <iostream>
#include <string>
#define NAME_LEN 20
#define Menu ("-----Menu-----\n1. 계좌개설\n2. 입    금\n3. 출    금\n4. 계좌정보 전체 줄력\n5. 프로그램 종료\n선택: ")
#define MAX_ACCID 100

using namespace std;

class Account
{
protected:
	Account* member[MAX_ACCID];
	Account* depositPassbookMember[MAX_ACCID];
	long long SSN; //주민등록번호
	int accID; //계좌번호
	int balance; //잔액
	char* cusName; //고객이름
public:
	Account(long long SSN, int accID, int balance, char* cusName)
		:accID(accID), SSN(SSN), balance(balance)
	{
		this->cusName = new char[NAME_LEN];
		strcpy_s(this->cusName, NAME_LEN, cusName);
	}

	Account() {

	}

	Account(const Account& acc)
		:accID(acc.accID), SSN(acc.SSN), balance(acc.balance)
	{
		cout << "복사생성자 생성" << endl;
		this->cusName = new char[NAME_LEN];
		strcpy_s(this->cusName, NAME_LEN, acc.cusName);
	}
	virtual ~Account() {
		delete[] cusName;
	}

	int getBalance() const
	{
		return balance;
	}

	int deposit(int money)
	{
		balance = (int)((balance + money)* 1.01);
		return (int)((balance + money) * 0.1);
	}


	bool withdrawal(int money)
	{
		if (money > balance) {
			return false;
		}
		balance -= money;
		return true;
	}

	void printInfo() const {
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

class AccountManager : public Account
{
protected:
	int memberCount = 0;
	int depositPassbookMemberCount = 0;
	
public :
	void deposit() {

		int s_accid;
		int money;
		int interest;

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
				interest = member[i]->deposit(money);
				cout << money << "원 입금되었습니다. 현재 잔액은 " << member[i]->getBalance() << "원이고 이자액은 : "<<interest << "원입니다." << endl << endl;
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

	void makeAccid() {

		int accId;
		long long SSN;
		int balance;
		char cusName[NAME_LEN];

		if (memberCount == MAX_ACCID)
		{
			cout << "계좌를 더이상 생성할수 없습니다." << endl << endl;
			return;
		}
		cout << "[계좌개설]" << endl;
		cout << "계좌ID: ";
		cin >> accId;
		for (int i = 0; i < memberCount; i++)
		{
			if (member[i]->checkId(accId))
			{
				cout << "동일한 계좌번호가 존재합니다." << endl << endl;
				return;
			}
		}
		cout << "주민등록번호: ";
		cin >> SSN;
		for (int i = 0; i < memberCount; i++)
		{
			if (member[i]->checkSSN(SSN))
			{
				cout << "한사람당 계좌는 1개씩만 만들수있습니다." << endl << endl;
				return;
			}
		}
		cout << "이  름: ";
		cin >> cusName;
		cout << "입금액: ";
		cin >> balance;
		if (balance < 10)
		{
			cout << "입금액을 10원이상 넣어주세요." << endl << endl;
			return;
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

class depositPassbook : public AccountManager{
public:

	int deposit(int money)
	{
		balance = (int)((balance + money)* 1.02);
		return (int)((balance + money) * 0.2);
	}

	void withdrawal() {
		if (depositPassbookMemberCount == 0)
		{
			cout << "계좌가 존재하지 않습니다." << endl << endl;
			return;
		}

		int s_accid;
		int money;

		cout << "[출   금]" << endl;
		cout << "계좌ID: ";
		cin >> s_accid;

		for (int i = 0; i < depositPassbookMemberCount; i++)
		{
			if (depositPassbookMember[i]->checkId(s_accid))
			{
				cout << "출금액: ";
				cin >> money;

				if (money <= 0)
				{
					cout << "출금금액은 최소 1원 이상이여야 합니다." << endl << endl;
					return;
				}

				bool check = depositPassbookMember[i]->withdrawal(money);

				if (!check)
				{
					cout << "출금 금액이 현재 잔액보다 많습니다." << endl << endl;
					return;
				}

				cout << money << "원 출금되었습니다. 현재 잔액은 " << depositPassbookMember[i]->getBalance() << "원입니다." << endl << endl;
				return;
			}
		}
		cout << "유효하지 않은 ID 입니다." << endl;
	}

	void printInfo() {
		if (depositPassbookMemberCount == 0)
		{
			cout << "계좌가 존재하지 않습니다." << endl << endl;
			return;
		}

		for (int i = 0; i < depositPassbookMemberCount; i++)
		{
			depositPassbookMember[i]->printInfo();
		}
	}

	void deposit() {

		int s_accid;
		int money;
		int interest;

		if (depositPassbookMemberCount == 0)
		{
			cout << "계좌가 존재하지 않습니다." << endl << endl;
			return;
		}

		cout << "[입   금]" << endl;
		cout << "계좌ID: ";
		cin >> s_accid;

		for (int i = 0; i < depositPassbookMemberCount; i++)
		{
			if (depositPassbookMember[i]->checkId(s_accid))
			{
				cout << "입금액: ";
				cin >> money;
				if (money <= 0)
				{
					cout << "입금금액은 최소 1원 이상이여야 합니다." << endl << endl;
					return;
				}
				interest = depositPassbookMember[i]->deposit(money);
				cout << money << "원 입금되었습니다. 현재 잔액은 " << member[i]->getBalance() << "원이고 이자액은 : " << interest << "원입니다." << endl << endl;
				return;
			}
		}
		cout << "유효하지 않은 ID 입니다." << endl;
	}

	void makeAccid()
	{
		int accId;
		long long SSN;
		int balance;
		char cusName[NAME_LEN];

		cout << "[예금계좌개설]" << endl;
		cout << "계좌ID: ";
		cin >> accId;
		for (int i = 0; i < depositPassbookMemberCount; i++)
		{
			if (depositPassbookMember[i]->checkId(accId))
			{
				cout << "동일한 계좌번호가 존재합니다." << endl << endl;
				return;
			}
		}
		cout << "주민등록번호: ";
		cin >> SSN;
		for (int i = 0; i < depositPassbookMemberCount; i++)
		{
			if (depositPassbookMember[i]->checkSSN(SSN))
			{
				cout << "한사람당 계좌는 1개씩만 만들수있습니다." << endl << endl;
				return;
			}
		}
		cout << "이  름: ";
		cin >> cusName;
		cout << "입금액: ";
		cin >> balance;

		if (balance < 10)
		{
			cout << "입금액을 10원이상 넣어주세요." << endl << endl;
			return;
		}

		for (int i = 0; i < memberCount; i++)
		{
			if (!member[i]->checkSSN(SSN))
			{
				cout << "기본 계좌를 생성해 주세요" << endl << endl;
				return;
			}
		}

		cout << "계좌가 성공적으로 개설되었습니다." << endl << endl;

		depositPassbookMember[depositPassbookMemberCount] = new Account(SSN, accId, balance, cusName);

		depositPassbookMemberCount++;
	}

};

int main() {
	AccountManager accManager;
	depositPassbook depositPassbook;
	int select;
	while (1) {
		cout << Menu;
		cin >> select;
		cout << endl;
		switch (select)
		{
		case 1:
			cout << "만들 계좌를 선택해주세요" << endl << "1. 기본계좌 생성" << endl << "2. 예금계좌 생성" << endl << "선택 : ";
			cin >> select;
			if (select == 1)
			{
				accManager.makeAccid();
			}
			else if (select == 2)
			{
				depositPassbook.makeAccid();
			}
			else
				cout << "계좌생성과 예금계좌생성중 선택해주세요" << endl << endl;
			break;
		case 2: 
			cout << "입금할 계좌를 선택해주세요" << endl << "1. 기본계좌 입금" << endl << "2. 예금계좌 입금" << endl << "선택 : ";
			cin >> select;
			if (select == 1)
			{
				accManager.deposit();
			}
			else if (select == 2)
			{
				depositPassbook.deposit();
			}
			else
				cout << "기본계좌 입금과 예금계좌 입금중 선택해주세요" << endl << endl;
			break;
		case 3: 
			cout << "출금할 계좌를 선택해주세요" << endl << "1. 기본계좌 출금" << endl << "2. 예금계좌 출금" << endl << "선택 : ";
			cin >> select;
			if (select == 1)
			{
				accManager.withdrawal();
			}
			else if (select == 2)
			{
				depositPassbook.withdrawal();
			}
			else
				cout << "기본계좌 출금과 예금계좌 출금중 선택해주세요" << endl << endl;
			break;
		case 4: 
			cout << "출력할 계좌를 선택해주세요" << endl << "1. 기본계좌 출력" << endl << "2. 예금계좌 출력" << endl << "선택 : ";
			cin >> select;
			if (select == 1)
			{
				accManager.printInfo();
			}
			else if (select == 2)
			{
				depositPassbook.printInfo();
			}
			else
				cout << "기본계좌 출력과 예금계좌 출력중 선택해주세요" << endl << endl;
			break;
		case 5:
			accManager.endProgram();
			return 0;
		default: "1~6중에 골라주십시오.";
			break;
		}
	}
}