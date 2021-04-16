#ifndef STRUTIL_H
#define STRUTIL_H

#include "WString.h"

class StrUtilClass {
	public:
		char* str2cptr(String str);
		const char* str2ccptr(String str);
};

char* StrUtilClass::str2cptr(String str) {
	char* output;
	str.toCharArray(output, str.length());
	return output;
}

const char* StrUtilClass::str2ccptr(String str) {
	return str.c_str();
}

StrUtilClass StrUtil();

#endif