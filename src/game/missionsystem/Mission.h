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
	std::string m_startLocationName;
	std::string m_endLocationName;
	std::string m_materialName;
public:
	Mission();
	Mission(std::string, std::string, bool, bool, float, int, std::string, std::string, std::string);
	~Mission();

	std::string getMessage();
	std::string getShortMessage();
	bool getRepeatStatus();
	bool getTimedStatus();
	float getMaxCompletionTime();
	int getMaterialCompletionAmnt();
	std::string getMaterialName();
	std::string getStartLocationName();
	std::string getEndLocationName();
};
