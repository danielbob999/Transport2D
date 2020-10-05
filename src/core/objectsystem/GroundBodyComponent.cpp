#include "GroundBodyComponent.h"
#include "../physics/PhysicsSystem.h"
#include "../console/Console.h"
#include "../renderer/GLIncludes.h"
#include "../renderer/RenderSystem.h"
using namespace core_objectsystem;

GroundBodyComponent::GroundBodyComponent() {

}

void GroundBodyComponent::start() {
	b2BodyDef bd;
	m_body = core_physics::PhysicsSystem::getInstance()->getWorld()->CreateBody(&bd);

	b2EdgeShape shape;

	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 0.0f;
	fd.friction = 0.6f;

	shape.SetTwoSided(b2Vec2(-20.0f, 0.0f), b2Vec2(20.0f, 0.0f));
	m_fixtures.push_back(m_body->CreateFixture(&fd));

	float hs[10] = { 0.25f, 1.0f, 4.0f, 0.0f, 0.0f, -1.0f, -2.0f, -2.0f, -1.25f, 0.0f };

	float x = 20.0f, y1 = 0.0f, dx = 5.0f;

	for (int32 i = 0; i < 10; ++i) {
		float y2 = hs[i];
		shape.SetTwoSided(b2Vec2(x, y1), b2Vec2(x + dx, y2));
		m_fixtures.push_back(m_body->CreateFixture(&fd));
		y1 = y2;
		x += dx;
	}

	for (int32 i = 0; i < 10; ++i) {
		float y2 = hs[i];
		shape.SetTwoSided(b2Vec2(x, y1), b2Vec2(x + dx, y2));
		m_fixtures.push_back(m_body->CreateFixture(&fd));
		y1 = y2;
		x += dx;
	}

	shape.SetTwoSided(b2Vec2(x, 0.0f), b2Vec2(x + 40.0f, 0.0f));
	m_fixtures.push_back(m_body->CreateFixture(&fd));

	x += 80.0f;
	shape.SetTwoSided(b2Vec2(x, 0.0f), b2Vec2(x + 40.0f, 0.0f));
	m_fixtures.push_back(m_body->CreateFixture(&fd));

	x += 40.0f;
	shape.SetTwoSided(b2Vec2(x, 0.0f), b2Vec2(x + 10.0f, 5.0f));
	m_fixtures.push_back(m_body->CreateFixture(&fd));

	x += 20.0f;
	shape.SetTwoSided(b2Vec2(x, 0.0f), b2Vec2(x + 40.0f, 0.0f));
	m_fixtures.push_back(m_body->CreateFixture(&fd));

	x += 40.0f;
	shape.SetTwoSided(b2Vec2(x, 0.0f), b2Vec2(x, 20.0f));
	m_fixtures.push_back(m_body->CreateFixture(&fd));

	core_physics::PhysicsSystem::getInstance()->registerDrawableComponent(this);

	Console::log("Started GroundBodyComponent");
}

void GroundBodyComponent::update() {
}

void GroundBodyComponent::close() {

}

void GroundBodyComponent::draw() {
	glBegin(GL_LINES);

	for (int i = 0; i < m_fixtures.size(); i++) {
		b2EdgeShape* shape = (b2EdgeShape*)m_fixtures[i]->GetShape();
		b2Vec2 vert1sc = core_renderer::RenderSystem::worldToScreenCoords(shape->m_vertex1);
		b2Vec2 vert2sc = core_renderer::RenderSystem::worldToScreenCoords(shape->m_vertex2);

		glVertex2f(vert1sc.x, vert1sc.y);
		glVertex2f(vert2sc.x, vert2sc.y);
	}

	glEnd();
}

b2Body* GroundBodyComponent::getBody() {
	return m_body;
}

std::vector<b2Fixture*>& GroundBodyComponent::getFixtures() {
	return m_fixtures;
}

std::string GroundBodyComponent::getTypeString() {
	return "GroundBodyComponent";
}

GroundBodyComponent::~GroundBodyComponent() {

}