#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<conio.h>
#include<ctime>
#include"speechmanager.h"
using namespace std;

int main()
{
	srand((unsigned int)time(0));

	speechmanager sm;
	
	int choice;

	/*for (map<int, speaker>::iterator it = sm.m_speaker.begin(); it != sm.m_speaker.end(); it++)
	{
		cout << "��ţ�" << it->first << "  ������" << it->second.m_name << endl;
	}*/

	while (1)
	{
		sm.showmenu();
		cout << "����������ѡ��";
		cin >> choice;
		while (choice<0||choice>3||cin.fail()) {
			cin.ignore();
			if (cin.fail()) {
				char cl;
				while ((cl = getchar()) != '\n');
				cin.clear();
			}
			cout << "����������������룺";
			cin >> choice;
		}

		switch (choice)
		{
		case 1:sm.startspeech(); break;

		case 2:sm.showrecord(); break;

		case 3:sm.clearrecord(); break;
			
		case 0:sm.exitspeechmanager(); break;

		default: {};

		}
		system("cls");
	}
}