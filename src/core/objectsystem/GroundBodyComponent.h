#pragma once
#include "ComponentScript.h"
#include "DrawablePhysicsComponent.h"
#include "box2d/box2d.h"
#include <vector>

namespace core_objectsystem {
	class GroundBodyComponent : public DrawablePhysicsComponent {
	private:
		std::vector<b2Fixture*> m_ground1Fixtures;
		std::vector<b2Fixture*> m_ground2Fixtures;
		b2Body* m_ground1Body;
		b2Body* m_ground2Body;
		int m_groundMode; // 1 if ground1 is active , 2 if ground2 is active
	public:
		GroundBodyComponent();
		~GroundBodyComponent();

		void start() override;
		void update() override;
		void close() override;

		void draw() override;
		void generate() override;

		std::string getTypeString() override;
	};
}
