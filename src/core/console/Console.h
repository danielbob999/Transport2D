#pragma once
#include <string>
#include <iostream>
#include <vector>

struct LogMsg {
	int msgCode;
	std::string* msg;
};

class Console {
private:
	static Console* s_instance;
	std::vector<LogMsg> m_messages;

	void saveToFile();
	std::string generateLogStr(const int&, const std::string&);
public:
	Console();
	~Console();

	static void log(const std::string&);
	static void log(const char*);
	static void logError(const std::string&);
	static void logError(const char*);

	static Console* getInstance();
};
