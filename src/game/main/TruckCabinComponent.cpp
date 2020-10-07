#include "TruckCabinComponent.h"
#include "../../core/objectsystem/Object.h"
#include "../../core/physics/PhysicsSystem.h"
#include "../../core/console/Console.h"
#include "../../core/renderer/Camera.h"
#include "../../core/input/InputSystem.h"
#include "../../core/input/InputKeyDefs.h"
#include <iostream>

TruckCabinComponent::TruckCabinComponent() {
	m_scale = 1;
}

void TruckCabinComponent::start() {
	generate();

	core_physics::PhysicsSystem::getInstance()->registerDrawableComponent(this);
}

void TruckCabinComponent::update() {
	Object* thisObject = Object::getObjectById(getParentId());
	thisObject->setPosition(m_truck->GetPosition());
	thisObject->setRotation(-m_truck->GetAngle());

	std::cout << "ObjectPos: (" << thisObject->getPosition().x << ", " << thisObject->getPosition().y << ")" << std::endl;
	
	b2Vec2 pos = core_renderer::Camera::getInstance()->getPosition();
	//core_renderer::Camera::getInstance()->setPosition();

	if (core_input::InputSystem::isKeyHeld(KEYBOARD_KEY_D)) {
		m_spring1->SetMotorSpeed(-100);
		m_spring2->SetMotorSpeed(-100);
		std::cout << "Truck going right" << std::endl;
	}
	else {
		m_spring1->SetMotorSpeed(0);
		m_spring2->SetMotorSpeed(0);
	}

	/*
	if (core_input::InputSystem::isKeyDown(KEYBOARD_KEY_D)) {
		m_spring1->SetMotorSpeed(-100);
		m_spring2->SetMotorSpeed(-100);
		std::cout << "Truck going left" << std::endl;
	}

	if (core_input::InputSystem::isKeyDown(KEYBOARD_KEY_S)) {
		m_spring1->SetMotorSpeed(0);
		m_spring2->SetMotorSpeed(0);
		std::cout << "Truck stopping" << std::endl;
	}*/

	core_renderer::Camera::getInstance()->setPosition(thisObject->getPosition().x, core_renderer::Camera::getInstance()->getPosition().y);
} 

void TruckCabinComponent::close() {

}

void TruckCabinComponent::draw() {
	using namespace core_renderer;
	return;
	// Draw the polygons
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	b2Vec2 objectPos = Object::getObjectById(getParentId())->getPosition();
	for (int i = 0; i < m_cabinFixtures.size(); i++) {
		b2PolygonShape* shape = (b2PolygonShape*)m_cabinFixtures[i]->GetShape();
		b2Vec2* verts = shape->m_vertices;
		b2Vec2 vert1sc = core_renderer::RenderSystem::worldToScreenCoords(verts[0] + m_truck->GetPosition());
		b2Vec2 vert2sc = core_renderer::RenderSystem::worldToScreenCoords(verts[1] + m_truck->GetPosition());
		b2Vec2 vert3sc = core_renderer::RenderSystem::worldToScreenCoords(verts[2] + m_truck->GetPosition());
		b2Vec2 vert4sc = core_renderer::RenderSystem::worldToScreenCoords(verts[3] + m_truck->GetPosition());

		glVertex2f(vert1sc.x, vert1sc.y);
		glVertex2f(vert2sc.x, vert2sc.y);

		glVertex2f(vert2sc.x, vert2sc.y);
		glVertex2f(vert3sc.x, vert3sc.y);

		glVertex2f(vert3sc.x, vert3sc.y);
		glVertex2f(vert4sc.x, vert4sc.y);

		glVertex2f(vert4sc.x, vert4sc.y);
		glVertex2f(vert1sc.x, vert1sc.y);
	}

	glEnd();


	glBegin(GL_LINE_LOOP);
	// Draw the wheels
	for (int i = 0; i < 3; i++) {
		b2Vec2 wheelPos = m_wheels[i]->GetPosition();
		// Loop 100 times creating line segments
		for (int j = 0; j < 100; j++) {
			b2CircleShape* shape = (b2CircleShape*)m_wheelFixtures[i]->GetShape();
			float theta = 2.0f * 3.1415926f * float(j) / float(100);//get the current angle 
			float x = shape->m_radius * cosf(theta);//calculate the x component 
			float y = shape->m_radius * sinf(theta);//calculate the y component 

			b2Vec2 posInScreenSpace = core_renderer::RenderSystem::worldToScreenCoords(b2Vec2(x + wheelPos.x, y + wheelPos.y));
			glVertex2f(posInScreenSpace.x, posInScreenSpace.y);//output vertex 
		}
	}

	glEnd();
}

void TruckCabinComponent::generate() {
	/*
	b2PolygonShape chassis;
	b2Vec2 vertices[8];
	b2Vec2 bodyOffset = getBodyOffset();

	vertices[0].Set((-2.8f * m_scale) + bodyOffset.x, (-0.5f * m_scale) + bodyOffset.y);
	vertices[1].Set((1.5f * m_scale) + bodyOffset.x, (-0.5f * m_scale) + bodyOffset.y);
	vertices[2].Set((1.5f * m_scale) + bodyOffset.x, (0.2f * m_scale) + bodyOffset.y);
	vertices[3].Set((-2.8f * m_scale) + bodyOffset.x, (0.2f * m_scale) + bodyOffset.y);
	chassis.Set(vertices, 4);

	b2PolygonShape cabin;
	vertices[0].Set((-1.0f * m_scale) + bodyOffset.x, (0.2f * m_scale) + bodyOffset.y);
	vertices[1].Set((1.5f * m_scale) + bodyOffset.x, (0.2f * m_scale) + bodyOffset.y);
	vertices[2].Set((1.5f * m_scale) + bodyOffset.x, (2.0f * m_scale) + bodyOffset.y);
	vertices[3].Set((-1.0f * m_scale) + bodyOffset.x, (2.0f * m_scale) + bodyOffset.y);
	cabin.Set(vertices, 4);

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	b2Vec2 objectPos = Object::getObjectById(getParentId())->getPosition();
	bd.position.Set(objectPos.x + getBodyOffset().x, objectPos.y + getBodyOffset().y);
	m_cabinBody = core_physics::PhysicsSystem::getInstance()->getWorld()->CreateBody(&bd);
	m_cabinFixtures.push_back(m_cabinBody->CreateFixture(&chassis, 1.0f));
	m_cabinFixtures.push_back(m_cabinBody->CreateFixture(&cabin, 1.0f));

	// ======================
	//   Setting the wheels
	b2CircleShape circle;
	circle.m_radius = (0.5f);

	

	b2FixtureDef fd;
	fd.shape = &circle;
	fd.density = 1.0f;
	fd.friction = 0.9f;

	bd.position.Set((-1.0f), (0.3));
	m_wheels[0] = core_physics::PhysicsSystem::getInstance()->getWorld()->CreateBody(&bd);
	m_wheelFixtures[0] = m_wheels[0]->CreateFixture(&fd);

	bd.position.Set((-2.0f), (0.3));
	m_wheels[1] = core_physics::PhysicsSystem::getInstance()->getWorld()->CreateBody(&bd);
	m_wheelFixtures[1] = m_wheels[1]->CreateFixture(&fd);

	bd.position.Set((0.8f), (0.3));
	m_wheels[2] = core_physics::PhysicsSystem::getInstance()->getWorld()->CreateBody(&bd);
	m_wheelFixtures[2] = m_wheels[2]->CreateFixture(&fd);

	b2WheelJointDef jd;
	b2Vec2 axis(0.0f, 1.0f);

	float mass1 = m_wheels[0]->GetMass();
	float mass2 = m_wheels[1]->GetMass();
	float mass3 = m_wheels[2]->GetMass();

	float hertz = 4.0f;
	float dampingRatio = 0.7f;
	float omega = 2.0f * b2_pi * hertz;

	jd.Initialize(m_cabinBody, m_wheels[0], m_wheels[0]->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 20.0f;
	jd.enableMotor = true;
	jd.stiffness = mass1 * omega * omega;
	jd.damping = 2.0f * mass1 * dampingRatio * omega;
	jd.lowerTranslation = -0.25f;
	jd.upperTranslation = 0.25f;
	jd.enableLimit = true;
	m_wheelJointSprings[0] = (b2WheelJoint*)core_physics::PhysicsSystem::getInstance()->getWorld()->CreateJoint(&jd);

	jd.Initialize(m_cabinBody, m_wheels[1], m_wheels[1]->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 20.0f;
	jd.enableMotor = true;
	jd.stiffness = mass2 * omega * omega;
	jd.damping = 2.0f * mass2 * dampingRatio * omega;
	jd.lowerTranslation = -0.25f;
	jd.upperTranslation = 0.25f;
	jd.enableLimit = true;
	m_wheelJointSprings[1] = (b2WheelJoint*)core_physics::PhysicsSystem::getInstance()->getWorld()->CreateJoint(&jd);

	jd.Initialize(m_cabinBody, m_wheels[2], m_wheels[2]->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 10.0f;
	jd.enableMotor = false;
	jd.stiffness = mass3 * omega * omega;
	jd.damping = 2.0f * mass3 * dampingRatio * omega;
	jd.lowerTranslation = -0.25f;
	jd.upperTranslation = 0.25f;
	jd.enableLimit = true;
	m_wheelJointSprings[2] = (b2WheelJoint*)core_physics::PhysicsSystem::getInstance()->getWorld()->CreateJoint(&jd);
	*/
	b2PolygonShape chassis;
	b2Vec2 vertices[8];
	vertices[0].Set(-2.5f, -0.5f);
	vertices[1].Set(1.5f, -0.5f);
	vertices[2].Set(1.5f, 0.2f);
	vertices[3].Set(-2.5f, 0.2f);
	chassis.Set(vertices, 4);

	b2PolygonShape cabin;
	vertices[0].Set(-1.0f, 0.2f);
	vertices[1].Set(1.5f, 0.2f);
	vertices[2].Set(1.5f, 2.0f);
	vertices[3].Set(-1.0f, 2.0f);
	cabin.Set(vertices, 4);


	b2CircleShape circle;
	circle.m_radius = 0.5f;

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(0.0f, 1.0f);
	m_truck = core_physics::PhysicsSystem::getInstance()->getWorld()->CreateBody(&bd);
	m_truck->CreateFixture(&chassis, 1.0f);
	m_truck->CreateFixture(&cabin, 1.0f);
	//m_cabinFixtures.push_back(m_truck->CreateFixture(&chassis, 1.0f));
	//m_cabinFixtures.push_back(m_truck->CreateFixture(&cabin, 1.0f));
	
	b2FixtureDef fd;
	fd.shape = &circle;
	fd.density = 1.0f;
	fd.friction = 0.9f;

	bd.position.Set(-1.0f, 0.35f);
	m_wheel1 = core_physics::PhysicsSystem::getInstance()->getWorld()->CreateBody(&bd);
	m_wheelFixtures[0] = m_wheel1->CreateFixture(&fd);
	m_wheels[0] = m_wheel1;

	bd.position.Set(-2.0f, 0.35f);
	m_wheel2 = core_physics::PhysicsSystem::getInstance()->getWorld()->CreateBody(&bd);
	m_wheelFixtures[1] = m_wheel2->CreateFixture(&fd);
	m_wheels[1] = m_wheel2;

	bd.position.Set(0.8f, 0.35f);
	m_wheel3 = core_physics::PhysicsSystem::getInstance()->getWorld()->CreateBody(&bd);
	m_wheelFixtures[2] = m_wheel3->CreateFixture(&fd);
	m_wheels[2] = m_wheel3;

	b2WheelJointDef jd;
	b2Vec2 axis(0.0f, 1.0f);

	float mass1 = m_wheel1->GetMass();
	float mass2 = m_wheel2->GetMass();
	float mass3 = m_wheel3->GetMass();

	float hertz = 4.0f;
	float dampingRatio = 1.0f;
	float omega = 2.0f * b2_pi * hertz;

	jd.Initialize(m_truck, m_wheel1, m_wheel1->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 20.0f;
	jd.enableMotor = true;
	jd.stiffness = mass1 * omega * omega;
	jd.damping = 2.0f * mass1 * dampingRatio * omega;
	jd.lowerTranslation = -0.25f;
	jd.upperTranslation = 0.25f;
	jd.enableLimit = true;
	m_spring1 = (b2WheelJoint*)core_physics::PhysicsSystem::getInstance()->getWorld()->CreateJoint(&jd);

	jd.Initialize(m_truck, m_wheel2, m_wheel2->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 20.0f;
	jd.enableMotor = true;
	jd.stiffness = mass2 * omega * omega;
	jd.damping = 2.0f * mass2 * dampingRatio * omega;
	jd.lowerTranslation = -0.25f;
	jd.upperTranslation = 0.25f;
	jd.enableLimit = true;
	m_spring2 = (b2WheelJoint*)core_physics::PhysicsSystem::getInstance()->getWorld()->CreateJoint(&jd);

	jd.Initialize(m_truck, m_wheel3, m_wheel3->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 10.0f;
	jd.enableMotor = false;
	jd.stiffness = mass3 * omega * omega;
	jd.damping = 2.0f * mass3 * dampingRatio * omega;
	jd.lowerTranslation = -0.25f;
	jd.upperTranslation = 0.25f;
	jd.enableLimit = true;
	m_spring3 = (b2WheelJoint*)core_physics::PhysicsSystem::getInstance()->getWorld()->CreateJoint(&jd);
}

std::string TruckCabinComponent::getTypeString() {
	return "TruckCabinComponent";
}

TruckCabinComponent::~TruckCabinComponent() {

}