// NextNDay.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "NextNDayCal.h"
#include "NumberCheck.h"
#include "InputFormat.h"
#include "OutputFormat.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	/*Format format("yyyy//mm//dd");
	string str = "1999//565//565";
	vector<string> v = format.match(str);
	for (vector<string>::const_iterator iter = v.cbegin(); iter != v.end(); ++iter) {
		cout << *iter << endl;
	}*/
	/*Date now;
	cout << "Today is :";
	cin >> now;

	while (true) {
		cout << "Enter Day Length: ";
		long long dayNum = 0;
		cin >> dayNum;
		cout << "Next " << dayNum << " Day Is: " << now.getNextNDay(dayNum);
	}*/

	ifstream in;
	ofstream out;
	in.open("E:\\Project\\data.csv");
	out.open("E:\\Project\\result.csv");
	if (!in) {
		cout << "file open error!";
	}
	char str[100];
	while (in.getline(str, 100)) {
		string line(str);
		Format &inputFormat = InputFormat("yyyy,mm,dd,n");
		vector<string> v = inputFormat.match(line);
		int count = 0;
		for (vector<string>::const_iterator iter = v.cbegin(); iter != v.end(); ++iter) {
			if (!NumberCheck::checkNumberLegality(*iter)) {
				cout << *iter << " Format error!\n";
				out << "Format error!\n";
				break;
			}
			++count;
		}
		if (count != v.size()) {
			continue;
		}
		long long year = atoll(v.at(0).c_str());
		int month = atoi(v.at(1).c_str());
		long long day = atoll(v.at(2).c_str());
		
		/*Date now(year, month, day);
		if (!DateTool::checkLegality(now)) {
			cout << now << " Format error!\n";
			out << now << " Format error!\n";
			continue;
		}
		cout << "Today is :" << now << endl;
		out << "Today is :" << now << endl;*/
		
		long long dayNum = atoll(v.at(3).c_str());
		string result = NextNDayCal::getNextNDay(year, month, day, dayNum);
		cout << "Next " << dayNum << " Day Is: " << result << endl;
		out << result << endl;
		/*Date result = now.getNextNDay(dayNum);
		OutputFormat &outputFormat = OutputFormat("yyyy-mm-dd");
		result.loadOutputFormat(outputFormat);
		cout << "Next " << dayNum << " Day Is: " << result << endl;
		out << "Next " << dayNum << " Day Is: " << result << endl;*/
	}

	in.close();
	out.close();

    return 0;
}
