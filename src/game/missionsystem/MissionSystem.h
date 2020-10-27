#pragma once
#include "Mission.h"
#include "../../core/objectsystem/ComponentScript.h"
#include "../../core/objectsystem/Object.h"
#include <chrono>
using namespace core_objectsystem;

#define MISSION_DETECT_DIST 10.0f

class MissionSystem : public ComponentScript {
private:
	Mission m_missions[4];
	int m_currentMissionIndex;
	bool m_showFullUI;
	bool m_finishedMissions;
	double m_missionStartTime;
	Object* m_truckObject;
	int m_missionAmntCurrent;

	void checkForMissionCompletion();
	void finishMission();
public:
	MissionSystem();
	~MissionSystem();

	void start();
	void update();
	void close();
	std::string getTypeString();
};
