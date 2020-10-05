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
		bool m_renderDebug;
		bool m_showUI;
		std::vector<DrawablePhysicsComponent*> m_drawableComponents;
	public:
		PhysicsSystem();
		~PhysicsSystem();

		void start() override;
		void update(double) override;
		void render(double) override;
		void close() override;

		b2World* getWorld();
		bool getRenderDebugStatus();
		void setRenderDebugStatus(bool);
		bool getUIStatus();
		void setUIStatus(bool);
		void registerDrawableComponent(DrawablePhysicsComponent*);

		static PhysicsSystem* getInstance();
	};
}
