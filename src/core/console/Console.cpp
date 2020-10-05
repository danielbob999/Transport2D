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
	m_showUI = true;
}

void Console::update() {
	if (m_showUI) {
		std::string logStr = "";

		for (int i = 0; i < m_messages.size(); i++) {
			logStr += (*m_messages[i].msg) + "\n";
		}

		ImGui::SetNextWindowPos(ImVec2(5, 5), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(Camera::getInstance()->getScreenSize().x - 10, 400), ImGuiCond_FirstUseEver);
		ImGui::Begin("Console");

		ImGui::Text(logStr.c_str());
		char buffer[1024] = "";

		//ImGui::SetCursorPosY(380);
		ImGui::SetNextItemWidth(Camera::getInstance()->getScreenSize().x - 10);
		if (ImGui::InputText("", buffer, 1024, ImGuiInputTextFlags_EnterReturnsTrue)) {
			submitCommandCallback(buffer);
		}

		ImGui::End();
	}
}

void Console::submitCommandCallback(std::string data) {
	//Console::log("> " + data);
	logInput(data);
}

void Console::setUIStatus(bool val) {
	m_showUI = val;
}

bool Console::getUIStatus() {
	return m_showUI;
}

void Console::logInput(const std::string& str) {
	// MsgCodes: 0 = message, 1 = warning, 2 = error, 3 = input
	LogMsg lm = { 3, new std::string(getInstance()->generateLogStr(3, str)) };
	getInstance()->m_messages.push_back(lm);

	std::cout << *(lm.msg) << std::endl;
}

void Console::logInput(const char* str) {
	logInput(std::string(str));
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

std::string Console::ptrToString(void* ptr) {
	std::stringstream ss;
	ss << ptr;

	return ss.str();
}

std::string Console::generateLogStr(const int& mode, const std::string& msg) {
	std::stringstream ss;

	ss << "[" << std::fixed<< std::setprecision(3) << Core::getInstance()->getRunTime() << "][";

	switch (mode) {
		case 1:
			ss << "wrn";
			break;
		case 2:
			ss << "err";
			break;
		case 3:
			ss << "inp";
			break;
		default:
			ss << "msg";
			break;
	}

	ss << "] " << std::defaultfloat << msg;

	return ss.str();
}

Console* Console::getInstance() {
	return s_instance;
}

Console::~Console() {

}