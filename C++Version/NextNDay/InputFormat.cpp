#include "stdafx.h"
#include "InputFormat.h"

InputFormat::InputFormat() : Format("yyyy,mm,dd,n")
{
}

InputFormat::InputFormat(string type) : Format(type)
{
	int temp1 = (int)type.find("yyyy", 0);
	if (temp1 == -1) {
		cout << type << " error format\n";
		m_sFormatType = "";
		return;
	}
	int temp2 = (int)type.find("mm", temp1 + 4);
	if (temp2 == -1) {
		cout << type << " error format\n";
		m_sFormatType = "";
		return;
	}
	int temp3 = (int)type.find("dd", temp2 + 2);
	if (temp3 == -1) {
		cout << type << " error format\n";
		m_sFormatType = "";
		return;
	}
	int temp4 = (int)type.find("n", temp3 + 2);
	if (temp4 == -1) {
		cout << type << " error format\n";
		m_sFormatType = "";
		return;
	}
	string splite = m_sFormatType.substr(temp1 + 4, temp2 - temp1 - 4);
	m_vSplits.push_back(splite);
	splite = m_sFormatType.substr(temp2 + 2, temp3 - temp2 - 2);
	m_vSplits.push_back(splite);
	splite = m_sFormatType.substr(temp3 + 2, temp4 - temp3 - 2);
	m_vSplits.push_back(splite);
}

InputFormat::InputFormat(const InputFormat & inputFormat) : Format(inputFormat)
{
}

vector<string> InputFormat::match(string str)
{
	vector<string> words;
	for (vector<string>::const_iterator iter = m_vSplits.cbegin(); iter != m_vSplits.cend(); ++iter) {
		string splite = *iter;
		int index = (int)str.find(splite);
		if (index == -1) {
			words.clear();
			return words;
		}
		string temp = str.substr(0, index);
		words.push_back(temp);
		str = str.substr(index + splite.length());
	}
	string temp = str.substr(0);
	words.push_back(temp);

	return words;
}

InputFormat::~InputFormat()
{
}
