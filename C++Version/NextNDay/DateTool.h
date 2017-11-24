#pragma once
class Date;
class DateTool {
public:
	DateTool();
	static bool isLeapYear(long long year);
	static int getMonthDayLength(const Date& date);
	static bool checkLegality(const Date& date);
	//static void standardDate(Date *date);
	static long long getLengthBetweenDate(const Date &first, const Date &second);
	static Date getMedianDate(const Date &begin, const Date &end);
	static Date LookUpDate(Date& begin, Date& end, long long dayNum);

};