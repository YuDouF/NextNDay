#include "stdafx.h"
#include "DateTool.h"
#include "Date.h"
#include <iostream>
#include <math.h>
using namespace std;

DateTool::DateTool() 
{
}

bool DateTool::isLeapYear(long long year)
{
	if (year < 0) {
		year++;
	}
	if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
		return true;
	}
	
	return false;
}

int DateTool::getMonthDayLength(const Date& date)
{
	int month = date.m_nMonth;
	switch (month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
		break;
	case 2:
		return isLeapYear(date.m_nYear) ? 29 : 28;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
		break;
	default:
		break;
	}
	
	return 0;
}

bool DateTool::checkLegality(const Date & date)
{
	long long year = date.m_nYear;
	if (year == 0) {
		//cout << "checkLegality: Year illegal" << endl;
		return false;
	}
	int month = date.m_nMonth;
	if (month <= 0 || month > 12) {
		//cout << "checkLegality: Month illegal" << endl;
		return false; 
	}
	long long day = date.m_nDay;
	if (day <= 0 || day > getMonthDayLength(date)) {
		//cout << "checkLegality: Day illegal" << endl;
		return false;
	}
	return true;
}

//void DateTool::standardDate(Date * date)
//{
//	while (!checkLegality(*date)) {
//		if (date->m_nDay <= 0) {
//			if (date->m_nDay < -365) {
//				int temp = date->m_nYear - 1;
//				if (temp == 0) {
//					--temp;
//				}
//				if ((date->m_nMonth > 2 && isLeapYear(date->m_nYear)) || (date->m_nMonth <= 2 && isLeapYear(temp))) {
//					date->m_nDay += 366;
//					--date->m_nYear;
//				}
//				else {
//					date->m_nDay += 365;
//					--date->m_nYear;
//				}
//
//				if (date->m_nYear == 0) {
//					--date->m_nYear;
//				}
//				continue;
//			}
//
//			date->m_nMonth--;
//			if (date->m_nMonth <= 0) {
//				date->m_nMonth = 12;
//				date->m_nYear--;
//				if (date->m_nYear == 0) {
//					date->m_nYear--;
//				}
//			}
//			date->m_nDay += getMonthDayLength(*date);
//		}
//		else {
//			if (date->m_nDay > 365) {
//				int temp = date->m_nYear + 1;
//				if (temp == 0) {
//					++temp;
//				}
//				if ((date->m_nMonth <= 2 && isLeapYear(date->m_nYear)) || (date->m_nMonth > 2 && isLeapYear(temp))) {
//					date->m_nDay -= 366;
//					++date->m_nYear;
//				}
//				else {
//					date->m_nDay -= 365;
//					++date->m_nYear;
//				}
//
//				if (date->m_nYear == 0) {
//					++date->m_nYear;
//				}
//				continue;
//			}
//
//			date->m_nDay -= getMonthDayLength(*date);
//			date->m_nMonth++;
//			if (date->m_nMonth > 12) {
//				date->m_nMonth = 1;
//				date->m_nYear++;
//				if (date->m_nYear == 0) {
//					date->m_nYear++;
//				}
//			}
//		}
//	}
//
//	return;
//}

long long DateTool::getLengthBetweenDate(const Date & first, const Date & second)
{

	Date bigger, smaller;
	if (first > second) {
		bigger = first;
		smaller = second;
	}
	else {
		bigger = second;
		smaller = first;
	}

	long long numberYearCap = 0;
	long long leapToSmaller4, leapToSmaller100, leapToSmaller400, leapToBigger4, leapToBigger100, leapToBigger400;
	if (bigger.m_nYear != smaller.m_nYear) {
		long long leapYearCount;
		long long notLeapYearCount;
		if (bigger.m_nYear > 0 && smaller.m_nYear > 0) {	//两者年份都在公元后模4-模100+模400
			leapToSmaller4 = (abs(smaller.m_nYear)) / 4;	//计算包括本身的闰年数
			leapToSmaller100 = (abs(smaller.m_nYear)) / 100;
			leapToSmaller400 = (abs(smaller.m_nYear)) / 400;

			leapToBigger4 = (abs(bigger.m_nYear) - 1) / 4;	//计算不包括本身的闰年数
			leapToBigger100 = (abs(bigger.m_nYear) - 1) / 100;
			leapToBigger400 = (abs(bigger.m_nYear) - 1) / 400;

			leapYearCount = (leapToBigger4 - leapToBigger100 + leapToBigger400) - (leapToSmaller4 - leapToSmaller100 + leapToSmaller400);
			notLeapYearCount = bigger.m_nYear - smaller.m_nYear - leapYearCount;
		}
		else if(bigger.m_nYear > 0 && smaller.m_nYear < 0){	//大的一方年份都在公元后，小的一方在公元前
			leapToSmaller4 = (abs(smaller.m_nYear + 1) - 1) / 4;	//计算不包括本身的闰年数
			leapToSmaller100 = (abs(smaller.m_nYear + 1) - 1) / 100;
			leapToSmaller400 = (abs(smaller.m_nYear + 1) - 1) / 400;

			leapToBigger4 = (abs(bigger.m_nYear) - 1) / 4;	//计算不包括本身的闰年数
			leapToBigger100 = (abs(bigger.m_nYear) - 1) / 100;
			leapToBigger400 = (abs(bigger.m_nYear) - 1) / 400;

			leapYearCount = (leapToBigger4 - leapToBigger100 + leapToBigger400) + (leapToSmaller4 - leapToSmaller100 + leapToSmaller400);
			if (smaller.m_nYear != -1) {	//补偿-1为闰年
				leapYearCount++;
			}
			notLeapYearCount = bigger.m_nYear - smaller.m_nYear - leapYearCount - 1;	//减去0年
		}
		else {	//两者年份都在公元前
			leapToSmaller4 = (abs(smaller.m_nYear + 1) - 1) / 4;	//计算不包括本身的闰年数
			leapToSmaller100 = (abs(smaller.m_nYear + 1) - 1) / 100;
			leapToSmaller400 = (abs(smaller.m_nYear + 1) - 1) / 400;
			leapToSmaller4++;	//补偿-1闰年

			leapToBigger4 = (abs(bigger.m_nYear + 1)) / 4;	//计算包括本身的闰年数
			leapToBigger100 = (abs(bigger.m_nYear + 1)) / 100;
			leapToBigger400 = (abs(bigger.m_nYear + 1)) / 400;
			leapToBigger4++;	//补偿-1闰年

			leapYearCount = (leapToSmaller4 - leapToSmaller100 + leapToSmaller400) - (leapToBigger4 - leapToBigger100 + leapToBigger400);
			notLeapYearCount = bigger.m_nYear - smaller.m_nYear - leapYearCount;
		}
		numberYearCap = 365 * notLeapYearCount + 366 * leapYearCount;
		if (isLeapYear(smaller.m_nYear)) {	//补偿小年份包括2月29日
			if (smaller.m_nMonth < 2 || (smaller.m_nMonth == 2 && smaller.m_nDay != 29)) {
				numberYearCap++;
			}
		}
		if (isLeapYear(bigger.m_nYear)) {	//补偿大年份包括2月29日
			if (smaller.m_nMonth > 2 || (smaller.m_nMonth == 2 && smaller.m_nDay == 29)) {
				numberYearCap++;
			}
		}
	}
	
	int numberMonthCap = 0;
	if (bigger.m_nMonth >= smaller.m_nMonth) {
		for (int i = smaller.m_nMonth; i < bigger.m_nMonth; ++i) {
			numberMonthCap += getMonthDayLength(Date(bigger.m_nYear, i));
		}
	}else {
		for (int i = bigger.m_nMonth; i < smaller.m_nMonth; ++i) {
			numberMonthCap -= getMonthDayLength(Date(bigger.m_nYear, i));
		}
	}

	long long numberDayCap = bigger.m_nDay - smaller.m_nDay;
	return numberYearCap + numberMonthCap + numberDayCap;
}

Date DateTool::getMedianDate(const Date & begin, const Date & end)
{
	long long year = (end.m_nYear + begin.m_nYear) / 2;	//年份取半
	if (year == 0 || (begin.m_nYear < 0 && end.m_nYear < 0 && begin.m_nYear != end.m_nYear)) {	//排除0年，取半向下取整
		year--;
	}
	int month = begin.m_nMonth;
	long long day = begin.m_nDay;

	//每次在年、月、日中只调整一项
	if (begin.m_nYear < end.m_nYear) {	//调整年份
		if (year == begin.m_nYear) {	//说明begin的年份比end的年份少1
			int temp = (end.m_nMonth + 12 - begin.m_nMonth) / 2;
			if (temp == 0) {	//说明begin为12月，end为1月
				day += (getMonthDayLength(begin) - begin.m_nDay + end.m_nDay) / 2;
				if (day > 31) {
					day -= 31;
					temp = 1;
				}
			}
			month += temp;
			if (month > 12) {
				month -= 12;
				++year;
				if (year == 0) {
					++year;
				}
			}
		}
	}
	else if (begin.m_nMonth < end.m_nMonth) {	//年份相同，调整月份，可能造成月份与天数不匹配
		month = (end.m_nMonth + begin.m_nMonth) / 2;	//月份取半
		if (month == begin.m_nMonth) {	//说明begin的月份比end月份少1
			int length = getMonthDayLength(Date(begin.m_nYear, begin.m_nMonth));
			day += (end.m_nDay + length - begin.m_nDay) / 2;
			if (day > length) {
				day -= length;
				++month;
			}
		}
		int length = getMonthDayLength(Date(year, month));
		if (day > length) {	//调整天数与月份相匹配
			day = length;
		}
	}
	else {	//年份月份都相同，调整天数
		day = (end.m_nDay + begin.m_nDay) / 2;
	}

	return Date(year, month, day);
}

Date DateTool::LookUpDate(Date & begin, Date & end, long long dayNum)
{
	Date time;
	while (dayNum != 0) {
		Date temp = getMedianDate(begin, end);
		long long length = getLengthBetweenDate(temp, begin);
		if (length == dayNum) {
			time = temp;
			dayNum = 0;
		}
		else if (length < dayNum) {
			begin = temp;
			dayNum -= length;
		}
		else if (length > dayNum) {
			end = temp;
		}
	}

	return time;
}
