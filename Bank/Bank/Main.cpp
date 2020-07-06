#include <iostream>
#include <string>
#define NAME_LEN 20
#define Menu ("-----Menu-----\n1. ���°���\n2. ��    ��\n3. ��    ��\n4. �������� ��ü �ٷ�\n5. ���α׷� ����\n����: ")
#define MAX_ACCID 100

using namespace std;

class Account
{
protected:
	long long SSN; //�ֹε�Ϲ�ȣ
	int accID; //���¹�ȣ
	int balance; //�ܾ�
	char* cusName; //���̸�
public:
	//������
	Account(long long SSN, int accID, int balance, char* cusName)
		:accID(accID), SSN(SSN), balance(balance)
	{
		this->cusName = new char[NAME_LEN];
		strcpy_s(this->cusName, NAME_LEN, cusName);
	}

	//�⺻������
	Account() {

	}

	//���������
	Account(const Account& acc)
		:accID(acc.accID), SSN(acc.SSN), balance(acc.balance)
	{
		cout << "��������� ����" << endl;
		this->cusName = new char[NAME_LEN];
		strcpy_s(this->cusName, NAME_LEN, acc.cusName);
	}

	//�Ҹ���
	virtual ~Account() {
		delete[] cusName;
	}

	//�ܾ��� ��ȯ���ִ� �Լ�
	int getBalance() const
	{
		return balance;
	}

	//���ڸ� ��ȯ���ִ� �Լ�
	virtual int deposit()
	{
		int interest = (int)((double)balance * 0.01);
		balance += interest;
		return interest;
	}

	//������ִ� �Լ�
	bool withdrawal(int money)
	{
		if (money > balance) {
			return false;
		}
		balance -= money;
		return true;
	}

	//�Ա����ִ� �Լ�
	bool addMomey(int money)
	{
		if (money < 0)
		{
			return false;
		}
		balance += money;
		return true;
	}

	//���������� ������ִ� �Լ�
	void printInfo() const {
		cout << "����ID: " << accID << endl;
		cout << "��  ��: " << cusName << endl;
		cout << "��  ��: " << balance << endl << endl;
	}
	
	//id�� üũ���ִ� �Լ�
	bool checkId(int id) const
	{
		return id == accID;
	}

	//�ֹε�Ϲ�ȣ�� üũ���ִ� �Լ�
	bool checkSSN(long long SSN) const
	{
		return SSN == this->SSN;
	}
};

class DepositPassbook : public Account {
public:
	DepositPassbook(long long input_SSN, int input_accID, int input_balance, char* input_cusName) : Account(input_SSN, input_accID, input_balance, input_cusName)
	{

	}

	virtual int deposit()
	{
		int interest = (int)((double)balance * 0.02);
		balance += interest;
		return interest;
	}

};

class AccountManager
{
protected:
	Account *member[MAX_ACCID];
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
				bool check = member[i]->addMomey(money);

				if (!check)
				{
					cout << "�Աݾ��� 0�� �̻����� ���ֽʽÿ�." << endl << endl;
					return;
				}

				int interest = member[i]->deposit();

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

	void makeAccid(int select) {

		int accId;
		long long SSN;
		int balance;
		char *cusName = new char[NAME_LEN];
		bool checkSSN = false;

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
		if (select == 1)
		{
			for (int i = 0; i < memberCount; i++)
			{
				if (member[i]->checkSSN(SSN))
				{
					cout << "�ѻ���� ���´� 1������ ������ֽ��ϴ�." << endl << endl;
					return;
				}
			}
		}
		else {
			for (int i = 0; i < memberCount; i++)
			{
				if (member[i]->checkSSN(SSN))
					checkSSN = true;
			}
			if (checkSSN == false)
			{
				cout << "���ݰ��¸� �����ϰ� �ʹٸ� ������¸� �������ֽʽÿ�" << endl << endl;
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

		if (select == 1) {
			member[memberCount] = new Account(SSN, accId, balance, cusName);
		}
		else {
			member[memberCount] = new DepositPassbook(SSN, accId, balance, cusName);
		}
			
		memberCount++;
	}

	void endProgram() {
		for (int i = 0; i < memberCount; i++)
			delete member[i];
	}
};

int main() {

	AccountManager accManager;

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
			cout << endl;
			if ((select == 2) || (select == 1))
			{
				accManager.makeAccid(select);
				break;
			}
			cout << "���»����� ���ݰ��»����� �������ּ���" << endl << endl;
			break;
		case 2: 
			accManager.deposit();
			break;
		case 3: 
			accManager.withdrawal();
			break;
		case 4: 
			accManager.printInfo();
			break;
		case 5:
			accManager.endProgram();
			return 0;
		default: "1~6�߿� ����ֽʽÿ�.";
			break;
		}
	}
}