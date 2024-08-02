#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include<iostream>
#include<ctime>
using namespace std;

void showtime(time_t time) {
	struct tm* p;
	p = localtime(&time);
	printf("%04d.%02d.%02d  %02d:%02d:%02d", p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
}


void m_clean() {
	char cl;
	while ((cl = getchar()) != '\n');
	cin.clear();

}