#include "PhysicsSystem.h"
#include "../console/Console.h"
#include <sstream>
#include <iostream>
using namespace core_physics;

PhysicsSystem* PhysicsSystem::s_instance = nullptr;

PhysicsSystem::PhysicsSystem() {
	if (s_instance != nullptr) {
		delete s_instance;
	}

	s_instance = this;

	Console::log("PhysicsSystem (" + Console::ptrToString(this) + ") has been initialised");
}

void PhysicsSystem::start() {
	m_debugDrawObject = new DebugDraw();
	m_debugDrawObject->Create();

	m_world = new b2World(b2Vec2(0, -9.8));
	m_world->SetDebugDraw(m_debugDrawObject);

	Console::log("PhysicsSystem (" + Console::ptrToString(this) + ") has successfully started");
}

void PhysicsSystem::update(double delta) {
	m_world->Step((1.0 / 60.0f), 6, 6);

	ImGui::Begin("Physics");

	std::stringstream ss;
	ss << "Gravity: (" << m_world->GetGravity().x << ", " << m_world->GetGravity().y << ")\n";
	ss << "Body Count: " << m_world->GetBodyCount() << std::endl;
	ImGui::Text(ss.str().c_str());
	ImGui::End();
}

void PhysicsSystem::render(double delta) {
	for (int i = 0; i < m_drawableComponents.size(); i++) {
		try {
			DrawablePhysicsComponent* dpc = m_drawableComponents[i];
			dpc->draw();
		} catch (const std::exception& e) {
			Console::logError("Failed to render DrawablePhysicsComponent. " + std::string(e.what()));
		}
	}
}

void PhysicsSystem::close() {
	Console::log("PhysicsSystem (" + Console::ptrToString(this) + ") has closed");
}

void PhysicsSystem::registerDrawableComponent(DrawablePhysicsComponent* comp) {
	std::vector<DrawablePhysicsComponent*>::iterator it = m_drawableComponents.begin();

	while (it != m_drawableComponents.end()) {
		if ((*it) == comp) {
			return; // If a component at the same address as already been registered, don't add it
		}

		it++;
	}

	m_drawableComponents.push_back(comp);
}

b2World* PhysicsSystem::getWorld() {
	return m_world;
}

b2Body* PhysicsSystem::getDebugDrawObject() {
	return body;
}

PhysicsSystem* PhysicsSystem::getInstance() {
	return s_instance;
}

PhysicsSystem::~PhysicsSystem() {

}
