#pragma once
#include <string>
#include <iostream>
#include <vector>

class Console {
private:
	static Console* s_instance;
	std::vector<std::string*> m_messages;

	void saveToFile();
public:
	Console();
	~Console();

	static void log(const std::string&);
	static void log(const char*);
	static Console* getInstance();
};
