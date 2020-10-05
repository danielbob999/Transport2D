#pragma once
#include "ComponentScript.h"
#include "DrawablePhysicsComponent.h"
#include "box2d/box2d.h"
#include <vector>

namespace core_objectsystem {
	class GroundBodyComponent : public DrawablePhysicsComponent {
	private:
		std::vector<b2Fixture*> m_fixtures;
		b2Body* m_body;
	public:
		GroundBodyComponent();
		~GroundBodyComponent();

		void start() override;
		void update() override;
		void close() override;

		void draw() override;

		b2Body* getBody();
		std::vector<b2Fixture*>& getFixtures();

		std::string getTypeString() override;
	};
}
