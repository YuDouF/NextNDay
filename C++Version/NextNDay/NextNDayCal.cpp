#include "stdafx.h"
#include "NextNDayCal.h"
#include "Date.h"
#include "DateTool.h"
#include "NumberCheck.h"
#include "InputFormat.h"
#include "OutputFormat.h"

NextNDayCal::NextNDayCal()
{
}


NextNDayCal::~NextNDayCal()
{
}

string NextNDayCal::getNextNDay(long long year, int month, long long day, long long numberDay)
{
	Date now(year, month, day);
	if (!DateTool::checkLegality(now)) {
		return "Format error!";
		//out << now << " Format error!\n";
	}
	cout << "Today is :" << now << endl;
	//out << "Today is :" << now << endl;

	long long dayNum = numberDay;
	Date result = now.getNextNDay(dayNum);
	result.loadOutputFormat(OutputFormat("yyyy-mm-dd"));
	return result.toString();
	//out << "Next " << dayNum << " Day Is: " << result << endl;
}
