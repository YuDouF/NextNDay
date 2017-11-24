#include "stdafx.h"
#include "OutputFormat.h"

OutputFormat::OutputFormat(): Format("yyyy-mm-dd")
{
}

OutputFormat::OutputFormat(string type) : Format(type)
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
	string splite = m_sFormatType.substr(temp1 + 4, temp2 - temp1 - 4);
	m_vSplits.push_back(splite);
	splite = m_sFormatType.substr(temp2 + 2, temp3 - temp2 - 2);
	m_vSplits.push_back(splite);
}

OutputFormat::OutputFormat(const OutputFormat & inputFormat) : Format(inputFormat)
{
}

vector<string> OutputFormat::match(string str)
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

OutputFormat::~OutputFormat()
{
}
