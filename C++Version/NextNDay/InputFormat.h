#pragma once
#include "Format.h"
#include <string>
using namespace std;
class InputFormat : public Format{
public:
	InputFormat();
	InputFormat(string type);
	InputFormat(const InputFormat & inputFormat);
	vector<string> match(string str);
	~InputFormat();
};