#include "stdafx.h"
#include "Date.h"
#include "DateTool.h"
#include <iostream>
#include <sstream>
#include <math.h>
//#include <time.h>
using namespace std;

Date::Date() : m_nYear(1), m_nMonth(1), m_nDay(1), m_fOutputFormat(OutputFormat("yyyy-mm-dd"))
{
	//struct tm currentTime;					//tm结构指针
	//time_t now;								//声明time_t类型变量
	//time(&now);								//获取系统日期和时间
	//localtime_s(&currentTime, &now);		//获取当地日期和时间

	//m_nYear = currentTime.tm_year + 1900;
	//m_nMonth = currentTime.tm_mon + 1;
	//m_nDay = currentTime.tm_mday;
}

Date::Date(long long year, int month) : m_nYear(year), m_nMonth(month), m_nDay(1), m_fOutputFormat(OutputFormat("yyyy-mm-dd"))
{
}

Date::Date(long long year, int month, long long day) : m_nYear(year), m_nMonth(month), m_nDay(day), m_fOutputFormat(OutputFormat("yyyy-mm-dd"))
{
	//DateTool::standardDate(this);
}

Date Date::operator+(long long dayNum)
{
	return Date(m_nYear, m_nMonth, m_nDay + dayNum);
}

Date::Date(const Date & date)
{
	m_nYear = date.m_nYear;
	m_nMonth = date.m_nMonth;
	m_nDay = date.m_nDay;
	m_fOutputFormat = date.m_fOutputFormat;
}

Date Date::getNextNDay(long long dayNum)
{
	Date maxDate, minDate;
	if (dayNum == 0) {
		return *this;
	}
	long long year = abs(dayNum) / 365;
	++year;
	if (dayNum > 0) {
		if (m_nMonth == 2 && m_nDay == 29) {	//避免2月29日进入程序逻辑
			m_nDay = 1;
			m_nMonth = 3;
			dayNum--;
		}
		year += m_nYear;
		if (year >= 0) {	//补偿0年
			++year;
		}
		maxDate = Date(year, m_nMonth, m_nDay);
		minDate = *this;
	}
	else{
		if (m_nMonth == 2 && m_nDay == 29) {	//避免2月29日进入程序逻辑
			m_nDay = 28;
			dayNum++;
		}
		year = m_nYear - year;
		if (year <= 0) {	//补偿0年
			--year;
		}
		maxDate = *this;
		minDate = Date(year, m_nMonth, m_nDay);
	
		dayNum = DateTool::getLengthBetweenDate(maxDate, minDate) + dayNum;	//将前N天转化为小日期的后M天
	}

	return DateTool::LookUpDate(minDate, maxDate, dayNum);
}

bool Date::operator>(const Date & date) const
{
	if (m_nYear > date.m_nYear) {
		return true;
	}
	else if (m_nYear == date.m_nYear) {
		if (m_nMonth > date.m_nMonth) {
			return true;
		}
		else if (m_nMonth == date.m_nMonth) {
			if (m_nDay >= date.m_nDay) {
				return true;
			}
		}
	}

	return false;
}

bool Date::operator<(const Date & date) const
{
	return !operator>(date);
}

void Date::loadOutputFormat(const OutputFormat & outputFormat)
{
	m_fOutputFormat = outputFormat;
}

string Date::toString()
{
	stringstream str("");
	vector<string> splits = m_fOutputFormat.getSplits();
	str << m_nYear << splits.at(0) << m_nMonth << splits.at(1) << m_nDay;
	string temp;
	str >> temp;
	return temp;
}

ostream & operator<<(ostream & os, const Date & date) 
{
	OutputFormat outputFormat = date.m_fOutputFormat;
	vector<string> splits = outputFormat.getSplits();

	os << date.m_nYear
		<< splits.at(0) << date.m_nMonth
		<< splits.at(1) << date.m_nDay;
	

	return os;
}

istream & operator>>(istream & is, Date & date)
{
	is >> date.m_nYear >> date.m_nMonth >> date.m_nDay;
	return is;
}
