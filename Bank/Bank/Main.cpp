#include <iostream>
#include <string>
#define NAME_LEN 20
#define Menu ("-----Menu-----\n1. ���°���\n2. ��    ��\n3. ��    ��\n4. �������� ��ü �ٷ�\n5. ���α׷� ����\n����: ")
#define MAX_ACCID 100

using namespace std;

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

void deposit(Account **member, int &count) {

	int s_accid;
	int money;

	if (count == 0)
	{
		cout << "���°� �������� �ʽ��ϴ�." << endl << endl;
		return;
	}

	cout << "[��   ��]" << endl;
	cout << "����ID: ";
	cin >> s_accid;

	for (int i = 0; i < count; i++)
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

void withdrawal(Account **member, int &count) {
	if (count == 0)
	{
		cout << "���°� �������� �ʽ��ϴ�." << endl << endl;
		return;
	}

	int s_accid;
	int money;

	cout << "[��   ��]" << endl;
	cout << "����ID: ";
	cin >> s_accid;

	for (int i = 0; i < count; i++)
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

			if(!check)
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

void printInfo(Account **member, int &count) {
	if (count == 0)
	{
		cout << "���°� �������� �ʽ��ϴ�." << endl << endl;
		return;
	}

	for (int i = 0; i < count; i++)
	{
		member[i]->printInfo();
	}
}

int makeAccid(Account **member, int &count) {

	int accId;
	long long SSN;
	int balance;
	char cusName[NAME_LEN];

	if (count == MAX_ACCID)
	{
		cout << "���¸� ���̻� �����Ҽ� �����ϴ�." << endl << endl;
		return -1;
	}
	cout << "[���°���]" << endl;
	cout << "����ID: ";
	cin >> accId;
	for (int i = 0; i <count; i++)
	{
		if (member[i]->checkId(accId))
		{
			cout << "������ ���¹�ȣ�� �����մϴ�." << endl << endl;
			return -1;
		}
	}
	cout << "�ֹε�Ϲ�ȣ: ";
	cin >> SSN;
	for (int i = 0; i < count; i++)
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

	member[count] = new Account(SSN, accId, balance, cusName);

	return 5;
}

void main() {
	Account *member[MAX_ACCID];
	int select, count = 0;
	int &refCount = count;
	while (1) {
		cout << Menu;
		cin >> select;
		cout << endl;
		switch (select)
		{
		case 1: 
			if (makeAccid(member, refCount) == 5)
				count++;
			break;
		case 2: deposit(member, refCount);
			break;
		case 3: withdrawal(member, refCount);
			break;
		case 4: printInfo(member, refCount);
			break;
		case 5:
			for(int i=0; i<count; i++)
				delete member[i];
			return;
		default: "1~5�߿� ����ֽʽÿ�.";
			break;
		}
	}
}