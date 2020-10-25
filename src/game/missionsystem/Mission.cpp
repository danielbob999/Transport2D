#include "Mission.h"

Mission::Mission() {

}

Mission::Mission(std::string message, std::string messageShort, bool repeat, bool isTimed, float time, int amnt) {
	m_message = message;
	m_messageShort = messageShort;
	m_repeatUntilComplete = repeat;
	m_isTimed = isTimed;
	m_maxCompletionTime = time;
	m_materialsCompletionAmnt = amnt;
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

Mission::~Mission() {

}