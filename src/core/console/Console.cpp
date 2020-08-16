#include "Console.h"
#include <iomanip>
#include "../Core.h"

/* Static Variables */
Console* Console::s_instance = nullptr;

Console::Console() {
	if (s_instance != nullptr) {
		delete s_instance;
	}

	s_instance = this;
}

void Console::log(const std::string& str) {
	getInstance()->m_messages.push_back(new std::string(str));

	std::cout << "[" << std::setprecision(3) << Core::getInstance()->getRunTime() << "][msg] " << str << std::endl;
}

void Console::log(const char* charStr) {
	log(std::string(charStr));
}

Console* Console::getInstance() {
	return s_instance;
}

Console::~Console() {

}