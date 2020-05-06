#include <iostream>
#include <string>
#define NAME_LEN 20
#define Menu ("-----Menu-----\n1. ���°���\n2. ��    ��\n3. ��    ��\n4. �������� ��ü �ٷ�\n5. ���α׷� ����\n����: ")

using namespace std;


typedef struct
{
	int accID; //���¹�ȣ
	int balance; //�ܾ�
	char cusName[NAME_LEN]; //���̸�
}Account;

void Deposit(Account *member, int *count) {

	if (*count == 0)
	{
		cout << "���°� �������� �ʽ��ϴ�." << endl << endl;
		return;
	}
	int s_accid;
	int money;

	cout << "[��   ��]" << endl;
	cout << "����ID: ";
	cin >> s_accid;

	for (int i = 0; i < *count; i++)
	{
		if (member[i].accID == s_accid)
		{
			cout << "�Աݾ�: ";
			cin >> money;
			if (money <= 0)
			{
				cout << "�Աݱݾ��� �ּ� 1�� �̻��̿��� �մϴ�." << endl << endl;
				return;
			}
			member[i].balance += money;
			cout << money << "�� �ԱݵǾ����ϴ�. ���� �ܾ��� " << member[i].balance << "���Դϴ�." << endl << endl;
			return;
		}
	}
	cout << "��ȿ���� ���� ID �Դϴ�." << endl;
}

void Withdrawal(Account *member, int *count) {
	if (*count == 0)
	{
		cout << "���°� �������� �ʽ��ϴ�." << endl << endl;
		return;
	}

	int s_accid;
	int money;

	cout << "[��   ��]" << endl;
	cout << "����ID: ";
	cin >> s_accid;

	for (int i = 0; i < *count; i++)
	{
		if (member[i].accID == s_accid)
		{
			cout << "��ݾ�: ";
			cin >> money;
			if (money > member[i].balance)
			{
				cout << "��� �ݾ��� ���� �ܾ׺��� �����ϴ�." << endl << endl;
				return;
			}
			else if (money <= 0)
			{
				cout << "��ݱݾ��� �ּ� 1�� �̻��̿��� �մϴ�." << endl << endl;
				return;
			}
			member[i].balance -= money;
			cout << money << "�� ��ݵǾ����ϴ�. ���� �ܾ��� " << member[i].balance << "���Դϴ�." << endl << endl;
			return;
		}
	}
	cout << "��ȿ���� ���� ID �Դϴ�." << endl;
}

void PrintInfo(Account *member, int *count) {
	if (*count == 0)
	{
		cout << "���°� �������� �ʽ��ϴ�." << endl << endl;
		return;
	}

	for (int i = 0; i < *count; i++)
	{
		cout << "����ID: " << member[i].accID << endl;
		cout << "��  ��: " << member[i].cusName << endl;
		cout << "��  ��: " << member[i].balance << endl << endl;
	}
}

void MakeAccid(Account *member, int *count) {
	if (*count == 100)
	{
		cout << "���¸� ���̻� �����Ҽ� �����ϴ�." << endl << endl;
		return;
	}
	cout << "[���°���]" << endl;
	cout << "����ID: ";
	cin >> member[*count].accID;
	for (int i = 0; i < *count; i++)
	{
		if (member[*count].accID == member[i].accID)
		{
			cout << "������ ���¹�ȣ�� �����մϴ�." << endl << endl;
			return;
		}
	}
	cout << "��  ��: ";
	cin >> member[*count].cusName;
	cout << "�Աݾ�: ";
	cin >> member[*count].balance;
	if (member[*count].balance < 10)
	{
		cout << "�Աݾ��� 10���̻� �־��ּ���." << endl << endl;
		return;
	}
	cout << "���°� ���������� �����Ǿ����ϴ�." << endl << endl;
	(*count)++;
}

void main() {
	Account *member = new Account[100];
	int select, count = 0;
	while (1) {
		cout << Menu;
		cin >> select;
		cout << endl;
		switch (select)
		{
		case 1: MakeAccid(member, &count);
			break;
		case 2: Deposit(member, &count);
			break;
		case 3: Withdrawal(member, &count);
			break;
		case 4: PrintInfo(member, &count);
			break;
		case 5:
			if (member != NULL)
				delete[] member;
			return;
		default: "1~5�߿� ����ֽʽÿ�.";
			break;
		}
	}
}