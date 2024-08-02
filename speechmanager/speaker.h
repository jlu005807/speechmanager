#pragma once
#include<iostream>

using namespace std;

class speaker
{
public:
	string m_name;
	double m_score[2];

	speaker() {};
	speaker(string name, double score1, double score2)
	{
		this->m_name = name;
		this->m_score[0] = score1;
		this->m_score[1] = score2;
	}
};