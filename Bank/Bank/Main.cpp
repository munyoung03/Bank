#include <iostream>
#include <string>
#define NAME_LEN 20
#define Menu ("-----Menu-----\n1. ���°���\n2. ��    ��\n3. ��    ��\n4. �������� ��ü �ٷ�\n5. ���α׷� ����\n����: ")
#define MAX_ACCID 100

using namespace std;

class Account
{
protected:
	Account* member[MAX_ACCID];
	Account* depositPassbookMember[MAX_ACCID];
	long long SSN; //�ֹε�Ϲ�ȣ
	int accID; //���¹�ȣ
	int balance; //�ܾ�
	char* cusName; //���̸�
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
		cout << "��������� ����" << endl;
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
				interest = member[i]->deposit(money);
				cout << money << "�� �ԱݵǾ����ϴ�. ���� �ܾ��� " << member[i]->getBalance() << "���̰� ���ھ��� : "<<interest << "���Դϴ�." << endl << endl;
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

	void makeAccid() {

		int accId;
		long long SSN;
		int balance;
		char cusName[NAME_LEN];

		if (memberCount == MAX_ACCID)
		{
			cout << "���¸� ���̻� �����Ҽ� �����ϴ�." << endl << endl;
			return;
		}
		cout << "[���°���]" << endl;
		cout << "����ID: ";
		cin >> accId;
		for (int i = 0; i < memberCount; i++)
		{
			if (member[i]->checkId(accId))
			{
				cout << "������ ���¹�ȣ�� �����մϴ�." << endl << endl;
				return;
			}
		}
		cout << "�ֹε�Ϲ�ȣ: ";
		cin >> SSN;
		for (int i = 0; i < memberCount; i++)
		{
			if (member[i]->checkSSN(SSN))
			{
				cout << "�ѻ���� ���´� 1������ ������ֽ��ϴ�." << endl << endl;
				return;
			}
		}
		cout << "��  ��: ";
		cin >> cusName;
		cout << "�Աݾ�: ";
		cin >> balance;
		if (balance < 10)
		{
			cout << "�Աݾ��� 10���̻� �־��ּ���." << endl << endl;
			return;
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
			cout << "���°� �������� �ʽ��ϴ�." << endl << endl;
			return;
		}

		int s_accid;
		int money;

		cout << "[��   ��]" << endl;
		cout << "����ID: ";
		cin >> s_accid;

		for (int i = 0; i < depositPassbookMemberCount; i++)
		{
			if (depositPassbookMember[i]->checkId(s_accid))
			{
				cout << "��ݾ�: ";
				cin >> money;

				if (money <= 0)
				{
					cout << "��ݱݾ��� �ּ� 1�� �̻��̿��� �մϴ�." << endl << endl;
					return;
				}

				bool check = depositPassbookMember[i]->withdrawal(money);

				if (!check)
				{
					cout << "��� �ݾ��� ���� �ܾ׺��� �����ϴ�." << endl << endl;
					return;
				}

				cout << money << "�� ��ݵǾ����ϴ�. ���� �ܾ��� " << depositPassbookMember[i]->getBalance() << "���Դϴ�." << endl << endl;
				return;
			}
		}
		cout << "��ȿ���� ���� ID �Դϴ�." << endl;
	}

	void printInfo() {
		if (depositPassbookMemberCount == 0)
		{
			cout << "���°� �������� �ʽ��ϴ�." << endl << endl;
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
			cout << "���°� �������� �ʽ��ϴ�." << endl << endl;
			return;
		}

		cout << "[��   ��]" << endl;
		cout << "����ID: ";
		cin >> s_accid;

		for (int i = 0; i < depositPassbookMemberCount; i++)
		{
			if (depositPassbookMember[i]->checkId(s_accid))
			{
				cout << "�Աݾ�: ";
				cin >> money;
				if (money <= 0)
				{
					cout << "�Աݱݾ��� �ּ� 1�� �̻��̿��� �մϴ�." << endl << endl;
					return;
				}
				interest = depositPassbookMember[i]->deposit(money);
				cout << money << "�� �ԱݵǾ����ϴ�. ���� �ܾ��� " << member[i]->getBalance() << "���̰� ���ھ��� : " << interest << "���Դϴ�." << endl << endl;
				return;
			}
		}
		cout << "��ȿ���� ���� ID �Դϴ�." << endl;
	}

	void makeAccid()
	{
		int accId;
		long long SSN;
		int balance;
		char cusName[NAME_LEN];

		cout << "[���ݰ��°���]" << endl;
		cout << "����ID: ";
		cin >> accId;
		for (int i = 0; i < depositPassbookMemberCount; i++)
		{
			if (depositPassbookMember[i]->checkId(accId))
			{
				cout << "������ ���¹�ȣ�� �����մϴ�." << endl << endl;
				return;
			}
		}
		cout << "�ֹε�Ϲ�ȣ: ";
		cin >> SSN;
		for (int i = 0; i < depositPassbookMemberCount; i++)
		{
			if (depositPassbookMember[i]->checkSSN(SSN))
			{
				cout << "�ѻ���� ���´� 1������ ������ֽ��ϴ�." << endl << endl;
				return;
			}
		}
		cout << "��  ��: ";
		cin >> cusName;
		cout << "�Աݾ�: ";
		cin >> balance;

		if (balance < 10)
		{
			cout << "�Աݾ��� 10���̻� �־��ּ���." << endl << endl;
			return;
		}

		for (int i = 0; i < memberCount; i++)
		{
			if (!member[i]->checkSSN(SSN))
			{
				cout << "�⺻ ���¸� ������ �ּ���" << endl << endl;
				return;
			}
		}

		cout << "���°� ���������� �����Ǿ����ϴ�." << endl << endl;

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
			cout << "���� ���¸� �������ּ���" << endl << "1. �⺻���� ����" << endl << "2. ���ݰ��� ����" << endl << "���� : ";
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
				cout << "���»����� ���ݰ��»����� �������ּ���" << endl << endl;
			break;
		case 2: 
			cout << "�Ա��� ���¸� �������ּ���" << endl << "1. �⺻���� �Ա�" << endl << "2. ���ݰ��� �Ա�" << endl << "���� : ";
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
				cout << "�⺻���� �Աݰ� ���ݰ��� �Ա��� �������ּ���" << endl << endl;
			break;
		case 3: 
			cout << "����� ���¸� �������ּ���" << endl << "1. �⺻���� ���" << endl << "2. ���ݰ��� ���" << endl << "���� : ";
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
				cout << "�⺻���� ��ݰ� ���ݰ��� ����� �������ּ���" << endl << endl;
			break;
		case 4: 
			cout << "����� ���¸� �������ּ���" << endl << "1. �⺻���� ���" << endl << "2. ���ݰ��� ���" << endl << "���� : ";
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
				cout << "�⺻���� ��°� ���ݰ��� ����� �������ּ���" << endl << endl;
			break;
		case 5:
			accManager.endProgram();
			return 0;
		default: "1~6�߿� ����ֽʽÿ�.";
			break;
		}
	}
}