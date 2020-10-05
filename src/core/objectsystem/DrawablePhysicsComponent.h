#pragma once
#include "ComponentScript.h"
namespace core_objectsystem {
	class DrawablePhysicsComponent : public ComponentScript{
	private:
	public:
		DrawablePhysicsComponent();
		~DrawablePhysicsComponent();

		virtual void start() {}
		virtual void update() {}
		virtual void close() {}

		virtual void draw() {}

		virtual std::string getTypeString();
	};
}
