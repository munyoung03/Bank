#include <iostream>
#include <string>
#define NAME_LEN 20
#define Menu ("-----Menu-----\n1. ���°���\n2. ��    ��\n3. ��    ��\n4. �������� ��ü �ٷ�\n5. ���α׷� ����\n����: ")
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
			cout << "���°� �������� �ʽ��ϴ�." << endl << endl;
			return;
		}

		cout << "[��   ��]" << endl;
		cout << "����ID: ";
		cin >> s_accid;

		for (int i = 0; i < memberCount; i++)
		{
			if (member[i]->checkId(s_accid))
			{
				cout << "�Աݾ�: ";
				cin >> money;
				if (money <= 0)
				{
					cout << "�Աݱݾ��� �ּ� 1�� �̻��̿��� �մϴ�." << endl << endl;
					return;
				}
				member[i]->deposit(money);
				cout << money << "�� �ԱݵǾ����ϴ�. ���� �ܾ��� " << member[i]->getBalance() << "���Դϴ�." << endl << endl;
				return;
			}
		}
		cout << "��ȿ���� ���� ID �Դϴ�." << endl;
	}
	

	void withdrawal() {
		if (memberCount == 0)
		{
			cout << "���°� �������� �ʽ��ϴ�." << endl << endl;
			return;
		}

		int s_accid;
		int money;

		cout << "[��   ��]" << endl;
		cout << "����ID: ";
		cin >> s_accid;

		for (int i = 0; i < memberCount; i++)
		{
			if (member[i]->checkId(s_accid))
			{
				cout << "��ݾ�: ";
				cin >> money;

				if (money <= 0)
				{
					cout << "��ݱݾ��� �ּ� 1�� �̻��̿��� �մϴ�." << endl << endl;
					return;
				}

				bool check = member[i]->withdrawal(money);

				if (!check)
				{
					cout << "��� �ݾ��� ���� �ܾ׺��� �����ϴ�." << endl << endl;
					return;
				}

				cout << money << "�� ��ݵǾ����ϴ�. ���� �ܾ��� " << member[i]->getBalance() << "���Դϴ�." << endl << endl;
				return;
			}
		}
		cout << "��ȿ���� ���� ID �Դϴ�." << endl;
	}

	void printInfo() {
		if (memberCount == 0)
		{
			cout << "���°� �������� �ʽ��ϴ�." << endl << endl;
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
			cout << "���¸� ���̻� �����Ҽ� �����ϴ�." << endl << endl;
			return -1;
		}
		cout << "[���°���]" << endl;
		cout << "����ID: ";
		cin >> accId;
		for (int i = 0; i < memberCount; i++)
		{
			if (member[i]->checkId(accId))
			{
				cout << "������ ���¹�ȣ�� �����մϴ�." << endl << endl;
				return -1;
			}
		}
		cout << "�ֹε�Ϲ�ȣ: ";
		cin >> SSN;
		for (int i = 0; i < memberCount; i++)
		{
			if (member[i]->checkSSN(SSN))
			{
				cout << "�ѻ���� ���´� 1������ ������ֽ��ϴ�." << endl << endl;
				return -1;
			}
		}
		cout << "��  ��: ";
		cin >> cusName;
		cout << "�Աݾ�: ";
		cin >> balance;
		if (balance < 10)
		{
			cout << "�Աݾ��� 10���̻� �־��ּ���." << endl << endl;
			return -1;
		}
		cout << "���°� ���������� �����Ǿ����ϴ�." << endl << endl;

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
	long long SSN; //�ֹε�Ϲ�ȣ
	int accID; //���¹�ȣ
	int balance; //�ܾ�
	char* cusName; //���̸�
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
		cout << "��������� ����" << endl;
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
		cout << "����ID: " << accID << endl;
		cout << "��  ��: " << cusName << endl;
		cout << "��  ��: " << balance << endl << endl;
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
		default: "1~5�߿� ����ֽʽÿ�.";
			break;
		}
	}
}