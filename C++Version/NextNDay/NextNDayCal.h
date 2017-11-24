#pragma once
#include <string>
using namespace std;

class NextNDayCal
{
public:
	NextNDayCal();
	~NextNDayCal();
	static string getNextNDay(long long year, int month, long long day, long long numberDay);
};

