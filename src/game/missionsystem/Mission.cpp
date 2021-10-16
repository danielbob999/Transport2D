#include "Mission.h"

Mission::Mission() {

}

Mission::Mission(std::string message, std::string messageShort, bool repeat, bool isTimed, float time, int amnt, std::string locationStart, std::string locationEnd, std::string matName) {
	m_message = message;
	m_messageShort = messageShort;
	m_repeatUntilComplete = repeat;
	m_isTimed = isTimed;
	m_maxCompletionTime = time;
	m_materialsCompletionAmnt = amnt;
	m_startLocationName = locationStart;
	m_endLocationName = locationEnd;
	m_materialName = matName;
}

std::string Mission::getMessage() {
	return m_message;
}

std::string Mission::getShortMessage() {
	return m_messageShort;
}

bool Mission::getRepeatStatus() {
	return m_repeatUntilComplete;
}

bool Mission::getTimedStatus() {
	return m_isTimed;
}

float Mission::getMaxCompletionTime() {
	return m_maxCompletionTime;
}

int Mission::getMaterialCompletionAmnt() {
	return m_materialsCompletionAmnt;
}

std::string Mission::getStartLocationName() {
	return m_startLocationName;
}

std::string Mission::getEndLocationName() {
	return m_endLocationName;
}

std::string Mission::getMaterialName() {
	return m_materialName;
}

Mission::~Mission() {

}