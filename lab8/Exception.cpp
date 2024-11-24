#include "Functions.h"

Exception::Exception(const char* msg, const string& contxt) :exception(msg)
{
	context = contxt;
	message = msg;
}
Exception::Exception()
{
	message = "Something went wrong";
	context = "Unknown";
}
std::string Exception::getContext() const
{
	return context;
}
std::string Exception::whatAndContext() const
{
	return context + ": " + message;
}