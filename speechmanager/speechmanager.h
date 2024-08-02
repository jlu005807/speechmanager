#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<string>
#include<fstream>
#include"speaker.h"
using namespace std;

class speechmanager
{
public:
	speechmanager();

	void showmenu();

	void exitspeechmanager();

	~speechmanager();

	vector<int>v1, v2, victory;

	map<int, speaker>m_speaker;
	
	int m_index;

	void initspeech();

	void createspeaker();

	void startspeech();

	void speechdraw();

	void speechcontest();

	void showscore();

	void saverecord();

	void loadrecord();

	bool fileempty;

	map<int, vector<string>>m_record;

	void showrecord();

	void clearrecord();
};