#pragma once
#include <string>

class Mission {
private:
	std::string m_message;
	std::string m_messageShort;
	bool m_repeatUntilComplete;
	bool m_isTimed;
	float m_maxCompletionTime;
	int m_materialsCompletionAmnt;
public:
	Mission();
	Mission(std::string, std::string, bool, bool, float, int);
	~Mission();

	std::string getMessage();
	std::string getShortMessage();
	bool getRepeatStatus();
	bool getTimedStatus();
	float getMaxCompletionTime();
	int getMaterialCompletionAmnt();
};
