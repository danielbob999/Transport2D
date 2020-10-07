#include "GroundBodyComponent.h"
#include "../physics/PhysicsSystem.h"
#include "../console/Console.h"
#include "../renderer/GLIncludes.h"
#include "../renderer/RenderSystem.h"
using namespace core_objectsystem;
using namespace core_physics;

GroundBodyComponent::GroundBodyComponent() {
	m_groundMode = 1;
}

void GroundBodyComponent::start() {
	generate();

	core_physics::PhysicsSystem::getInstance()->registerDrawableComponent(this);
	Console::log("Started GroundBodyComponent");
}

void GroundBodyComponent::update() {
}

void GroundBodyComponent::close() {

}

void GroundBodyComponent::draw() {
	std::vector<b2Fixture*> fixtures;

	switch (m_groundMode) {
	case 1:
		fixtures = m_ground1Fixtures;
		break;
	case 2:
		fixtures = m_ground2Fixtures;
		break;
	default:
		fixtures.clear();
		break;
	}

	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	for (int i = 0; i < fixtures.size(); i++) {
		b2EdgeShape* shape = (b2EdgeShape*)fixtures[i]->GetShape();
		b2Vec2 vert1sc = core_renderer::RenderSystem::worldToScreenCoords(shape->m_vertex1);
		b2Vec2 vert2sc = core_renderer::RenderSystem::worldToScreenCoords(shape->m_vertex2);

		glVertex2f(vert1sc.x, vert1sc.y);
		glVertex2f(vert2sc.x, vert2sc.y);
	}

	glEnd();
}

void GroundBodyComponent::generate() {
	// START OF GENERATION FOR GROUND 1
	b2BodyDef bd;
	m_ground1Body = PhysicsSystem::getInstance()->getWorld()->CreateBody(&bd);

	b2EdgeShape shape;

	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 0.0f;
	fd.friction = 0.6f;
	//shape texture = texture
	shape.SetTwoSided(b2Vec2(-20, 0.0f), b2Vec2(-20, 20.0f));
	m_ground1Fixtures.push_back(m_ground1Body->CreateFixture(&fd));

	shape.SetTwoSided(b2Vec2(-20.0f, 0.0f), b2Vec2(20.0f, 0.0f));
	m_ground1Fixtures.push_back(m_ground1Body->CreateFixture(&fd));

	shape.SetTwoSided(b2Vec2(370, -7.5f), b2Vec2(370.0f, 2.0f));
	m_ground1Fixtures.push_back(m_ground1Body->CreateFixture(&fd));

	shape.SetTwoSided(b2Vec2(615, 5.4f), b2Vec2(615, 10.0f));
	m_ground1Fixtures.push_back(m_ground1Body->CreateFixture(&fd));


	//245										//275
	float hs[500] = { 0.25f, 1.0f, 4.0f, 3.5f, 2.0f, 1.5f, 1.7f, 2.6f, 3.2f, 5.0f, 6.0f, 8.0f, 8.5f, 9.0f, 10.0f, 8.3f, 6.5f, 7.0f, 1.5f, -1.0f, -1.2f, 1.6f, 2.3f, 7.0f, 6.5f, 6.5f, 6.5f, 5.7f, 4.2f, 3.1f, 3.5f, 4.8f, 5.7f, 6.3f, 7.0f, 8.0f, 8.3f, 8.4f, 6.1f, 5.2f, 3.1f, 2.8f, 2.3f, 1.4f, 1.2f, 1.0f, 0.2f, -1.5f, -4.4f, -5.2f, -5.1f, -4.5f, -4.5f, -4.5f, -5.6f, -5.2f, -4.3f, -6.2f, -7.5f, -7.5f, -7.5f , -7.5f , -7.5f , -7.5f , -7.5f , -7.5f , -7.5f , -7.5f , -7.5f , -7.5f };

	float x = 20.0f, y1 = 0.0f, dx = 5.0f;

	for (int32 i = 0; i < 500; ++i)
	{
		if (hs[i] == NULL) {
			break;
		}
		float y2 = hs[i];
		shape.SetTwoSided(b2Vec2(x, y1), b2Vec2(x + dx, y2));
		m_ground1Fixtures.push_back(m_ground1Body->CreateFixture(&fd));
		y1 = y2;
		x += dx;
	}

	float js[500] = { 8.4, 8.9, 9.4, 9.9, 10.4, 12.0, 13.0, 14.5, 15.7, 16.3, 18.0, 19.0, 19.5, 19.4, 19.8, 17.9, 16.5, 15.4, 15.7, 15.9, 16.7, 17.5, 18.4, 18.6, 19.2, 20.0, 20.5, 20.9, 22.5, 22.8, 23.3, 24.4, 23.0, 22.5, 21.5, 19.5, 18.2, 19.8, 18.4, 17.5, 16.8, 16.1, 15.0, 14.7, 13.2, 12.9, 12.9, 12.9, 12.9, 11.5, 10.4, 9.9, 8.6, 7.3, 6.2, 7.4, 6.5, 5.4, 4.4, 4.4, 5.4, 6.5, 7.2, 7.2, 6.5, 5.4, 4.4, 4.4, 5.4, 5.4 , 5.4 , 5.4 , 5.4 , 5.4 , 5.4 , 5.4 , 5.4 , 5.4 , 5.4 , 5.4 , 5.4 };
	y1 = js[0];
	x = 210;

	for (int32 i = 0; i < 500; ++i)
	{
		if (js[i] == NULL) {
			break;
		}
		float y2 = js[i];
		shape.SetTwoSided(b2Vec2(x, y1), b2Vec2(x + dx, y2));
		m_ground1Fixtures.push_back(m_ground1Body->CreateFixture(&fd));
		y1 = y2;
		x += dx;
	}
	// END OF GENERATION FOR GROUND 1
}

std::string GroundBodyComponent::getTypeString() {
	return "GroundBodyComponent";
}

GroundBodyComponent::~GroundBodyComponent() {

}