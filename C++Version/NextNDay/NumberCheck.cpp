#include "stdafx.h"
#include "NumberCheck.h"
#include <iostream>
using namespace std;

bool NumberCheck::checkNumberLegality(string str)
{
	for (unsigned i = 0; i < str.length(); i++) {
		char temp = str[i];
		if (i == 0 && temp == '-') {
			if (str.length() == 1 || str[1] == '0') {
				//cout << str << " Format error!\n";
				return false;
			}
		}
		else if(i == 0 && temp == '0' && str.length() != 1){
			//cout << str << " Format error!\n";
			return false;
		}
		else if (temp < '0' || temp > '9') {
			//cout << str << " Format error!\n";
			return false;
		}
	}
	return true;
}
