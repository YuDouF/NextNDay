#pragma once
#include "Format.h"
class OutputFormat : public Format {
public:
	OutputFormat();
	OutputFormat(string type);
	OutputFormat(const OutputFormat & inputFormat);
	vector<string> match(string str);
	~OutputFormat();
};