#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;
class Format {
protected:
	string m_sFormatType;
	vector<string> m_vSplits;
public:
	Format();
	Format(string type);
	Format(const Format & format);
	Format& operator=(const Format & format);
	virtual vector<string> match(string str) = 0;
	vector<string> getSplits();
	void display();
	virtual ~Format();
};