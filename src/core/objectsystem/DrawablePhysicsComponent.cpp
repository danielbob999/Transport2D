#include "DrawablePhysicsComponent.h"
using namespace core_objectsystem;

DrawablePhysicsComponent::DrawablePhysicsComponent(){}
DrawablePhysicsComponent::~DrawablePhysicsComponent(){}

void DrawablePhysicsComponent::setBodyOffset(b2Vec2 offset) {
	m_bodyOffset = offset;
}

b2Vec2 DrawablePhysicsComponent::getBodyOffset() {
	return m_bodyOffset;
}

std::string DrawablePhysicsComponent::getTypeString() {
	return "DrawablePhysicsComponent";
}