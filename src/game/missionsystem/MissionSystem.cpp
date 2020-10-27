#include "MissionSystem.h"
#include "imgui/imgui.h"
#include "../../core/renderer/Camera.h"
#include "box2d/box2d.h"
#include "../../core/console/Console.h"
#include "../../core/input/InputKeyDefs.h"
#include "../../core/input/InputSystem.h"
#include "../main/TruckCabinComponent.h"
#include "../../core/Core.h"
#include <math.h>

using namespace core_renderer;
using namespace core_input;

MissionSystem::MissionSystem() {
	m_missions[0] = Mission("Hello and welcome to Transport2D. \n\n\I just got a phone call from Bazza down the way that needs dirt delivered to his tree farm. \n\nTask:\nLoad the truck up and head on over.", "Deliver the dirt to the mill", true, true, 30.0, 20);
	m_missions[1] = Mission("Well done with completing the first mission. Gazza has now contacted us from down in Crankshaft Mine with the request of some wood. \n\Task:\nTurn the  up to log pickup point, load up the truck, and deliver the logs to the mine.", "Deliver the logs to the mine", true, false, 0.0, 20);
	m_missions[2] = Mission("3rd mission text", "Take Metals from the Mine to the Mill", true, false, 0.0, 20);
	m_missions[3] = Mission("4th mission text", "Take wood from the Mill to the Quarry", true, false, 0.0, 20);
	m_currentMissionIndex = 0;
	m_showFullUI = true;
	m_finishedMissions = false;
	m_truckObject = nullptr;

	Console::log("Initalised MissionSystem");
}

void MissionSystem::start() {

}

void MissionSystem::update() {
	if (m_truckObject == nullptr) {
		m_truckObject = Object::getObjectByName("TruckObject");
	}

	if (m_currentMissionIndex > 3) {
		if (!m_showFullUI) {
			return;
		}

		int windowWidth = 400;
		int windowHeight = 300;
		b2Vec2 screenSize = Camera::getInstance()->getScreenSize();
		ImGui::SetNextWindowPos(ImVec2((screenSize.x / 2.0f) - (windowWidth / 2.0f), (screenSize.y / 2.0f) - (windowHeight / 2.0f)), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowBgAlpha(0.65f);
		ImGui::Begin("Finshed Missions");

		ImGui::TextWrapped("Well done on completing the mission in Transport2D.\n\nYou are now free to roam free and go meet Gazza, Bazza, Hazza and the rest of the gang in your own time!\n\nThank you for playing Transport2D!");

		int buttonWidth = 60;
		int buttonHeight = 20;
		ImGui::SetCursorPos(ImVec2(windowWidth - buttonWidth - 10, windowHeight - buttonHeight - 10)); // Move cursor on needed positions

		if (ImGui::Button("Close", ImVec2(buttonWidth, buttonHeight))) {
			m_showFullUI = false;
		}

		ImGui::End();
		return;
	}

	double missionTimeTaken = Core::getInstance()->getRunTime() - m_missionStartTime;
	double timeLeft = m_missions[m_currentMissionIndex].getMaxCompletionTime() - missionTimeTaken;

	if (timeLeft < 0) {
		// User has run out of time for the mission, display fail message
		timeLeft = 0;
	}

	if (m_showFullUI) {
		int windowWidth = 400;
		int windowHeight = 300;
		b2Vec2 screenSize = Camera::getInstance()->getScreenSize();
		ImGui::SetNextWindowPos(ImVec2((screenSize.x / 2.0f) - (windowWidth / 2.0f), (screenSize.y / 2.0f) - (windowHeight / 2.0f)), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowBgAlpha(0.65f);
		ImGui::Begin(std::string("Mission #" + std::to_string(m_currentMissionIndex + 1)).c_str(), NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		ImGui::TextWrapped(m_missions[m_currentMissionIndex].getMessage().c_str());
		
		int buttonWidth = 60;
		int buttonHeight = 20;
		ImGui::SetCursorPos(ImVec2(windowWidth - buttonWidth - 10, windowHeight - buttonHeight - 10)); // Move cursor on needed positions

		if (ImGui::Button("Ok", ImVec2(buttonWidth, buttonHeight))) {
			m_showFullUI = false;
			m_missionStartTime = Core::getInstance()->getRunTime();
		}

		ImGui::End();
	} else {
		ImGui::SetNextWindowPos(ImVec2(5, 250), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(400, 70), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowBgAlpha(0.65f);

		ImGui::Begin(std::string("Mission #" + std::to_string(m_currentMissionIndex + 1) + " (Double click to expand)").c_str(), NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

		if (ImGui::IsMouseDoubleClicked(0) && ImGui::IsItemHovered()) {
			m_showFullUI = true;
		}

		ImGui::TextWrapped(std::string(m_missions[m_currentMissionIndex].getShortMessage() + "\nTime Left: " + std::to_string(timeLeft)).c_str());

		ImGui::End();
	}

	checkForMissionCompletion();
}

void MissionSystem::close() {

}

void MissionSystem::checkForMissionCompletion() {
	if (InputSystem::isKeyDown(KEYBOARD_KEY_E)) {
		if (m_currentMissionIndex == 0) {
			// Calculate the distances to the main mission points
			float distanceToQuarryPnt = fabs(m_truckObject->getPosition().x - Object::getObjectByName("MissionPointQuarry")->getPosition().x);
			float distanceToMillPnt = fabs(m_truckObject->getPosition().x - Object::getObjectByName("MissionPointMill")->getPosition().x);

			// If the truck is near the quary, fill up the truck
			if (distanceToQuarryPnt < MISSION_DETECT_DIST) {
				TruckCabinComponent* comp = (TruckCabinComponent*)m_truckObject->getComponentScript("TruckCabinComponent");

				if (comp->getInventoryItemAmount() < m_missions[m_currentMissionIndex].getMaterialCompletionAmnt()) {
					Console::log("filled up now");
					comp->setInventoryItem("Dirt", m_missions[m_currentMissionIndex].getMaterialCompletionAmnt());
				}
			}

			if (distanceToMillPnt < MISSION_DETECT_DIST) {
				TruckCabinComponent* comp = (TruckCabinComponent*)m_truckObject->getComponentScript("TruckCabinComponent");

				// If the truck has the correct material and the correct amount, finish the mission
				if (comp->getInventoryItemAmount() >= m_missions[m_currentMissionIndex].getMaterialCompletionAmnt()) {
					finishMission();
				}
			}

			return;
		}

		if (m_currentMissionIndex == 1) {
			// Calculate the distances to the main mission points
			float distanceToMillPnt = fabs(m_truckObject->getPosition().x - Object::getObjectByName("MissionPointMill")->getPosition().x);
			float distanceToMinePnt = fabs(m_truckObject->getPosition().x - Object::getObjectByName("MissionPointMine")->getPosition().x);

			// If the truck is near the mill, fill up the truck
			if (distanceToMillPnt < MISSION_DETECT_DIST) {
				TruckCabinComponent* comp = (TruckCabinComponent*)m_truckObject->getComponentScript("TruckCabinComponent");

				if (comp->getInventoryItemAmount() < m_missions[m_currentMissionIndex].getMaterialCompletionAmnt()) {
					Console::log("filled up now");
					comp->setInventoryItem("Wood", m_missions[m_currentMissionIndex].getMaterialCompletionAmnt());
				}
			}

			if (distanceToMinePnt < MISSION_DETECT_DIST) {
				TruckCabinComponent* comp = (TruckCabinComponent*)m_truckObject->getComponentScript("TruckCabinComponent");

				// If the truck has the correct material and the correct amount, finish the mission
				if (comp->getInventoryItemAmount() >= m_missions[m_currentMissionIndex].getMaterialCompletionAmnt()) {
					finishMission();
				}
			}

			return;
		}

		if (m_currentMissionIndex == 2) {
			// Calculate the distances to the main mission points
			float distanceToMinePnt = fabs(m_truckObject->getPosition().x - Object::getObjectByName("MissionPointMine")->getPosition().x);
			float distanceToMillPnt = fabs(m_truckObject->getPosition().x - Object::getObjectByName("MissionPointMill")->getPosition().x);

			// If the truck is near the mine, fill up the truck
			if (distanceToMinePnt < MISSION_DETECT_DIST) {
				TruckCabinComponent* comp = (TruckCabinComponent*)m_truckObject->getComponentScript("TruckCabinComponent");

				if (comp->getInventoryItemAmount() < m_missions[m_currentMissionIndex].getMaterialCompletionAmnt()) {
					comp->setInventoryItem("Metal", m_missions[m_currentMissionIndex].getMaterialCompletionAmnt());
				}
			}

			if (distanceToMillPnt < MISSION_DETECT_DIST) {
				TruckCabinComponent* comp = (TruckCabinComponent*)m_truckObject->getComponentScript("TruckCabinComponent");

				// If the truck has the correct material and the correct amount, finish the mission
				if (comp->getInventoryItemAmount() >= m_missions[m_currentMissionIndex].getMaterialCompletionAmnt()) {
					finishMission();
				}
			}
			return;
		}

		if (m_currentMissionIndex == 3) {
			// Calculate the distances to the main mission points
			float distanceToMillPnt = fabs(m_truckObject->getPosition().x - Object::getObjectByName("MissionPointMill")->getPosition().x);
			float distanceToQuarryPnt = fabs(m_truckObject->getPosition().x - Object::getObjectByName("MissionPointQuarry")->getPosition().x);

			// If the truck is near the mill, fill up the truck
			if (distanceToMillPnt < MISSION_DETECT_DIST) {
				TruckCabinComponent* comp = (TruckCabinComponent*)m_truckObject->getComponentScript("TruckCabinComponent");

				if (comp->getInventoryItemAmount() < m_missions[m_currentMissionIndex].getMaterialCompletionAmnt()) {
					comp->setInventoryItem("Wood", m_missions[m_currentMissionIndex].getMaterialCompletionAmnt());
				}
			}

			if (distanceToQuarryPnt < MISSION_DETECT_DIST) {
				TruckCabinComponent* comp = (TruckCabinComponent*)m_truckObject->getComponentScript("TruckCabinComponent");

				// If the truck has the correct material and the correct amount, finish the mission
				if (comp->getInventoryItemAmount() >= m_missions[m_currentMissionIndex].getMaterialCompletionAmnt()) {
					finishMission();
				}
			}
			return;
		}
	}
}

void MissionSystem::finishMission() {
	Console::log("Finished mission " + std::to_string(m_currentMissionIndex + 1));
	m_currentMissionIndex++;

	TruckCabinComponent* comp = (TruckCabinComponent*)m_truckObject->getComponentScript("TruckCabinComponent");
	comp->setInventoryItem("Empty", 0);

	m_showFullUI = true;
}

std::string MissionSystem::getTypeString() {
	return "MissionSystemComponent";
}

MissionSystem::~MissionSystem() {

}