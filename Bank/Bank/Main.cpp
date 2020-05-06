#include <iostream>
#include <string>
#define NAME_LEN 20
#define Menu ("-----Menu-----\n1. 계좌개설\n2. 입    금\n3. 출    금\n4. 계좌정보 전체 줄력\n5. 프로그램 종료\n선택: ")

using namespace std;


typedef struct
{
	int accID; //계좌번호
	int balance; //잔액
	char cusName[NAME_LEN]; //고객이름
}Account;

void Deposit(Account *member, int *count) {

	if (*count == 0)
	{
		cout << "계좌가 존재하지 않습니다." << endl << endl;
		return;
	}
	int s_accid;
	int money;

	cout << "[입   금]" << endl;
	cout << "계좌ID: ";
	cin >> s_accid;

	for (int i = 0; i < *count; i++)
	{
		if (member[i].accID == s_accid)
		{
			cout << "입금액: ";
			cin >> money;
			if (money <= 0)
			{
				cout << "입금금액은 최소 1원 이상이여야 합니다." << endl << endl;
				return;
			}
			member[i].balance += money;
			cout << money << "원 입금되었습니다. 현재 잔액은 " << member[i].balance << "원입니다." << endl << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID 입니다." << endl;
}

void Withdrawal(Account *member, int *count) {
	if (*count == 0)
	{
		cout << "계좌가 존재하지 않습니다." << endl << endl;
		return;
	}

	int s_accid;
	int money;

	cout << "[출   금]" << endl;
	cout << "계좌ID: ";
	cin >> s_accid;

	for (int i = 0; i < *count; i++)
	{
		if (member[i].accID == s_accid)
		{
			cout << "출금액: ";
			cin >> money;
			if (money > member[i].balance)
			{
				cout << "출금 금액이 현재 잔액보다 많습니다." << endl << endl;
				return;
			}
			else if (money <= 0)
			{
				cout << "출금금액은 최소 1원 이상이여야 합니다." << endl << endl;
				return;
			}
			member[i].balance -= money;
			cout << money << "원 출금되었습니다. 현재 잔액은 " << member[i].balance << "원입니다." << endl << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID 입니다." << endl;
}

void PrintInfo(Account *member, int *count) {
	if (*count == 0)
	{
		cout << "계좌가 존재하지 않습니다." << endl << endl;
		return;
	}

	for (int i = 0; i < *count; i++)
	{
		cout << "계좌ID: " << member[i].accID << endl;
		cout << "이  름: " << member[i].cusName << endl;
		cout << "잔  액: " << member[i].balance << endl << endl;
	}
}

void MakeAccid(Account *member, int *count) {
	if (*count == 100)
	{
		cout << "계좌를 더이상 생성할수 없습니다." << endl << endl;
		return;
	}
	cout << "[계좌개설]" << endl;
	cout << "계좌ID: ";
	cin >> member[*count].accID;
	for (int i = 0; i < *count; i++)
	{
		if (member[*count].accID == member[i].accID)
		{
			cout << "동일한 계좌번호가 존재합니다." << endl << endl;
			return;
		}
	}
	cout << "이  름: ";
	cin >> member[*count].cusName;
	cout << "입금액: ";
	cin >> member[*count].balance;
	if (member[*count].balance < 10)
	{
		cout << "입금액을 10원이상 넣어주세요." << endl << endl;
		return;
	}
	cout << "계좌가 성공적으로 개설되었습니다." << endl << endl;
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
		default: "1~5중에 골라주십시오.";
			break;
		}
	}
}