#pragma once
#include "OutputFormat.h"
#include <iostream>
using namespace std;

class Date {
	friend class DateTool;
	friend ostream& operator <<(ostream &os, const Date &date);
	friend istream& operator >>(istream &is, Date &date);
private: 
	long long m_nYear;
	int m_nMonth;
	long long m_nDay;

	OutputFormat m_fOutputFormat;
public:
	Date();
	Date(long long year, int month);
	Date(const Date &date);
	Date(long long year, int month, long long day);
	Date operator +(long long dayNum);
	Date getNextNDay(long long dayNum);

	bool operator > (const Date &date) const;
	bool operator < (const Date & date) const;

	void loadOutputFormat(const OutputFormat &format);
	string toString();
};