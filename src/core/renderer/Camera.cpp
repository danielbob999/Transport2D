#include "Camera.h"
#include "../console/Console.h"
using namespace core_renderer;

Camera* Camera::s_instance = nullptr;

Camera::Camera(int sizeX, int sizeY) {
	if (s_instance != nullptr) {
		delete s_instance;
	}

	s_instance = this;

	m_position = b2Vec2(0, 0);
	m_zoomFactor = 1.0f;

	m_screenSize = b2Vec2(sizeX, sizeY);

	setDefaultDisplayAreaWidth(10);

	m_backgroundColour[0] = 0.8f;
	m_backgroundColour[1] = 0.8f;
	m_backgroundColour[2] = 0.8f;

	Console::log("Created a new Camera. ScreenWidth=" + std::to_string(sizeX) + ", ScreenHeight=" + std::to_string(sizeY));
}

b2Vec2& Camera::getPosition() {
	return m_position;
}

void Camera::setPosition(int x, int y) {
	m_position.x = x;
	m_position.y = y;
}

float Camera::getZoomFactor() {
	return m_zoomFactor;
}

void Camera::setZoomFactor(float zoomFact) {
	m_zoomFactor = zoomFact;
}

void Camera::setDefaultDisplayAreaWidth(float width) {
	m_defaultDisplayAreaWidth = width;

	// Find the screen ratio
	float screenRatio = (float)m_screenSize.y / (float)m_screenSize.x;

	Console::log("RATIO: " + std::to_string(screenRatio));

	// Set the display height amount to be the same ratio as the display width
	//	- This stops the rendering becoming distorted
	m_defaultDisplayAreaHeight = width * screenRatio;
}

float Camera::getDefaultDisplayAreaWidth() {
	return m_defaultDisplayAreaWidth;
}

float Camera::getDefaultDisplayAreaHeight() {
	return m_defaultDisplayAreaHeight;
}

float* Camera::getBackgroundColour() {
	return m_backgroundColour;
}

void Camera::setBackgroundColour(float r, float g, float b) {
	m_backgroundColour[0] = r;
	m_backgroundColour[1] = g;
	m_backgroundColour[2] = b;
}

b2Vec2& Camera::getScreenSize() {
	return m_screenSize;
}

Camera* Camera::getInstance() {
	return s_instance;
}

Camera::~Camera() {

}