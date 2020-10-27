#pragma once
#include "ComponentScript.h"
#include "box2d/box2d.h"
#include "../renderer/GLIncludes.h"
#include "../renderer/RenderSystem.h"
namespace core_objectsystem {
	class DrawablePhysicsComponent : public ComponentScript{
	private:
		b2Vec2 m_bodyOffset;
	public:
		DrawablePhysicsComponent();
		~DrawablePhysicsComponent();

		b2Vec2 getBodyOffset();
		void setBodyOffset(b2Vec2);

		virtual void start() {}
		virtual void update() {}
		virtual void close() {}

		virtual void draw() {}

		virtual void generate() {}

		virtual std::string getTypeString();
	};
}
