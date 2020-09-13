#include "InputSystem.h"
#include "../console/Console.h"
#include <algorithm>
using namespace core_input;

InputSystem* InputSystem::s_instance = nullptr;

InputSystem::InputSystem() {
	if (s_instance != nullptr) {
		delete s_instance;
	}

	s_instance = this;

	m_keysDownLocker = new bool[1024];
	m_keysDownThisFrame = new bool[1024];
	m_keysUpThisFrame = new bool[1024];
	m_keysHeldThisFrame = new bool[1024];
	m_keysHeldLastFrame = new bool[1024];

	for (int i = 0; i < 1024; i++) {
		m_keysDownLocker[i] = false;
		m_keysDownThisFrame[i] = false;
		m_keysUpThisFrame[i] = false;
		m_keysHeldLastFrame[i] = false;
		m_keysHeldThisFrame[i] = false;
	}

	Console::log("InputSystem (" + Console::ptrToString(s_instance) + ") has been initialised");
}

void InputSystem::inputCallbackFn(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (!getInstance()->m_keysDownLocker[key]) { // if the down press on this key isn't locked
			getInstance()->m_keysDownThisFrame[key] = true;
			getInstance()->m_keysDownLocker[key] = true;
		}

		getInstance()->m_keysHeldThisFrame[key] = true;
		return;
	}

	if (action == GLFW_RELEASE) {
		getInstance()->m_keysUpThisFrame[key] = true;
		getInstance()->m_keysHeldThisFrame[key] = false;

		getInstance()->m_keysDownLocker[key] = false; // Unlock the down key
		return;
	}
}

void InputSystem::start() {
	Console::log("InputSystem (" + Console::ptrToString(s_instance) + ") has started");
}

void InputSystem::update(double delta) {
	for (int i = 0; i < 1024; i++) {
		m_keysHeldLastFrame[i] = m_keysHeldThisFrame[i];

		m_keysDownThisFrame[i] = false;
		m_keysUpThisFrame[i] = false;
	}
}

void InputSystem::render(double delta) {

}

void InputSystem::close() {
	Console::log("InputSystem (" + Console::ptrToString(s_instance) + ") has closed");
}

bool InputSystem::isKeyDown(int key) {
	return getInstance()->m_keysDownThisFrame[key];
}

bool InputSystem::isKeyHeld(int key) {
	return getInstance()->m_keysHeldThisFrame[key];
}

bool InputSystem::isKeyUp(int key) {
	return getInstance()->m_keysUpThisFrame[key];
}

InputSystem* InputSystem::getInstance() {
	return s_instance;
}

InputSystem::~InputSystem() {
	delete[] m_keysDownLocker;
	delete[] m_keysDownThisFrame;
	delete[] m_keysUpThisFrame;
	delete[] m_keysHeldThisFrame;
	delete[] m_keysHeldLastFrame;
}