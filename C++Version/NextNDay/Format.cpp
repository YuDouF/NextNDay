#include "stdafx.h"
#include "Format.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

Format::Format(): m_sFormatType("")
{
}

Format::Format(string type): m_sFormatType(type)
{
}

Format::Format(const Format & format) : m_sFormatType(format.m_sFormatType), m_vSplits(format.m_vSplits)
{
}

Format & Format::operator=(const Format & format)
{
	m_sFormatType = format.m_sFormatType;
	m_vSplits = format.m_vSplits;
	return *this;
}

vector<string> Format::getSplits()
{
	return m_vSplits;
}

void Format::display()
{
	if (m_sFormatType == "") {
		return;
	}
	cout << "Format: " << m_sFormatType
		<< "\nSplites:\n";
	for (vector<string>::const_iterator iter = m_vSplits.cbegin(); iter != m_vSplits.end(); ++iter) {
		cout << *iter << endl;
	}
}

Format::~Format()
{
}
