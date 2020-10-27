#pragma once
#include "ComponentScript.h"
#include "DrawablePhysicsComponent.h"
#include "box2d/box2d.h"
#include "Object.h"
#include <vector>

namespace core_objectsystem {
	class GroundBodyComponent : public DrawablePhysicsComponent {
	private:
		std::vector<b2Fixture*> m_ground1Fixtures;
		std::vector<b2Fixture*> m_ground2Fixtures;
		b2Body* m_ground1Body;
		b2Body* m_ground2Body;
		std::vector<b2Body*> m_bridgeBodies;
		std::vector<Object*> m_bridgeObjects;
		int m_groundMode; // 1 if quarry-mill , 2 if quarry-mine only
	public:
		GroundBodyComponent();
		~GroundBodyComponent();

		void start() override;
		void update() override;
		void close() override;

		void draw() override;
		void generate() override;
		void setGroundMode(int);
		int getGroundMode();

		std::string getTypeString() override;
	};
}
