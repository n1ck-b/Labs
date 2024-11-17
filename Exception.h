#pragma once
#include "Functions.h"

using namespace std;

class Exception : public exception
{
public:
	Exception(const char* msg, const string& contxt = "Unknown");
	Exception();
	string getContext() const;
	string whatAndContext() const;
private:
	string message;
	string context;
};