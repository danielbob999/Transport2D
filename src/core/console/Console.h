#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "imgui/imgui.h"

struct LogMsg {
	int msgCode;
	std::string* msg;
};

class Console {
private:
	static Console* s_instance;
	std::vector<LogMsg> m_messages;
	bool m_showUI;

	void saveToFile();
	std::string generateLogStr(const int&, const std::string&);
	void submitCommandCallback(std::string);
	void logInput(const std::string&);
	void logInput(const char*);
public:
	Console();
	~Console();

	void update();
	bool getUIStatus();
	void setUIStatus(bool val);

	static void log(const std::string&);
	static void log(const char*);
	static void logError(const std::string&);
	static void logError(const char*);

	static std::string ptrToString(void*);

	static Console* getInstance();
};
