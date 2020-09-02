#include "Console.h"
#include <iomanip>
#include <sstream>
#include "../Core.h"

/* Static Variables */
Console* Console::s_instance = nullptr;

Console::Console() {
	if (s_instance != nullptr) {
		delete s_instance;
	}

	s_instance = this;
}

/* Regular log functions */
void Console::log(const std::string& str) {
	// MsgCodes: 0 = message, 1 = warning, 2 = error
	LogMsg lm = { 0, new std::string(getInstance()->generateLogStr(0, str)) };
	getInstance()->m_messages.push_back(lm);

	std::cout << *(lm.msg) << std::endl;
}

void Console::log(const char* charStr) {
	log(std::string(charStr));
}

void Console::logError(const std::string& str) {
	// MsgCodes: 0 = message, 1 = warning, 2 = error
	LogMsg lm = { 2, new std::string(getInstance()->generateLogStr(2, str)) };
	getInstance()->m_messages.push_back(lm);

	std::cout << *(lm.msg) << std::endl;
}

void Console::logError(const char* charStr) {
	logError(std::string(charStr));
}

std::string Console::generateLogStr(const int& mode, const std::string& msg) {
	std::stringstream ss;

	ss << "[" << std::setprecision(3) << Core::getInstance()->getRunTime() << "][";

	switch (mode) {
		case 1:
			ss << "wrn";
			break;
		case 2:
			ss << "err";
			break;
		default:
			ss << "msg";
			break;
	}

	ss << "] " << msg;

	return ss.str();
}

Console* Console::getInstance() {
	return s_instance;
}

Console::~Console() {

}