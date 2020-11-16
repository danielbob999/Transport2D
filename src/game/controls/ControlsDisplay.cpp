#include "ControlsDisplay.h"
#include "../../core/renderer/Camera.h"
#include <math.h>

using namespace core_renderer;

ControlsDisplay* ControlsDisplay::s_instance = nullptr;

ControlsDisplay::ControlsDisplay() {
	if (s_instance != nullptr) {
		delete s_instance;
	}

	s_instance = this;

	Console::log("ControlsDisplay (" + Console::ptrToString(s_instance) + ") has been initialised");
}

void ControlsDisplay::start() {
	Console::log("ControlsDisplay (" + Console::ptrToString(s_instance) + ") has been started");
}

void ControlsDisplay::update(double delta) {
	std::string str = "";

	for (int i = 0; i < m_entries.size(); i++) {
		str += std::string(m_entries[i].actionChar) + " - " + m_entries[i].message + "\n";
	}

	int windowWidth = 400;
	int windowHeight = 100;
	b2Vec2 screenSize = Camera::getInstance()->getScreenSize();
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowBgAlpha(0.65f);
	ImGui::Begin("Controls", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);

	ImGui::TextWrapped(str.c_str());
	ImGui::End();

	m_entries.clear();
}

void ControlsDisplay::render(double delta) {

}

void ControlsDisplay::close() {
	Console::log("ControlsDisplay (" + Console::ptrToString(s_instance) + ") has been closed");
}

void ControlsDisplay::registerControl(void* parent, std::string actionMsg, std::string key) {
	DisplayEntry de;
	de.parent = parent;
	de.message = actionMsg;
	de.actionChar = key;

	m_entries.push_back(de);
}

ControlsDisplay* ControlsDisplay::getInstance() {
	return s_instance;
}

ControlsDisplay::~ControlsDisplay() {

}