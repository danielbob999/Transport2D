#pragma once
#include "../coresystem/CoreSystem.h"
#include "../objectsystem/DrawablePhysicsComponent.h"
#include "draw.h"
#include "box2d/box2d.h"
#include <vector>

using namespace core_objectsystem;

namespace core_physics {
	class PhysicsSystem : public CoreSystem {
	private:
		static PhysicsSystem* s_instance;
		b2World* m_world;
		DebugDraw* m_debugDrawObject;
		std::vector<DrawablePhysicsComponent*> m_drawableComponents;

		// Testing
		b2Body* body;
	public:
		PhysicsSystem();
		~PhysicsSystem();

		void start() override;
		void update(double) override;
		void render(double) override;
		void close() override;

		b2World* getWorld();
		b2Body* getDebugDrawObject();
		void registerDrawableComponent(DrawablePhysicsComponent*);

		static PhysicsSystem* getInstance();
	};
}
