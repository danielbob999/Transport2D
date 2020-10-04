#pragma once
#include "../objectsystem/ComponentScript.h"
#include "box2d/box2d.h"
#include <vector>

namespace core_objectsystem {
	class GroundBodyComponent : public ComponentScript {
	private:
		std::vector<b2Fixture*> m_fixtures;
		b2Body* m_body;
	public:
		GroundBodyComponent();
		~GroundBodyComponent();

		void start();
		void update();
		void close();

		b2Body* getBody();
		std::vector<b2Fixture*>& getFixtures();

		std::string getTypeString();
	};
}
