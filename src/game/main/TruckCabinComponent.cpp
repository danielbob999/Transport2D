#include "TruckCabinComponent.h"
#include "../../core/objectsystem/Object.h"
#include "../../core/physics/PhysicsSystem.h"
#include "../../core/console/Console.h"
#include "../../core/renderer/Camera.h"
#include "../../core/input/InputSystem.h"
#include "../../core/input/InputKeyDefs.h"
#include "../../core/objectsystem/RenderComponent.h"
#include <iostream>

using namespace core_input;

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

	Object* trailerObject = Object::getObjectByName("TrailerObject");
	trailerObject->setPosition(m_trailer->GetPosition());
	trailerObject->setRotation(-m_trailer->GetAngle());

	//std::cout << "ObjectPos: (" << thisObject->getPosition().x << ", " << thisObject->getPosition().y << ")" << std::endl;
	
	b2Vec2 pos = core_renderer::Camera::getInstance()->getPosition();
	//core_renderer::Camera::getInstance()->setPosition();

	if (core_input::InputSystem::isKeyHeld(KEYBOARD_KEY_D)) {
		m_spring1->EnableMotor(true);
		m_spring2->EnableMotor(true);
		m_spring1->SetMotorSpeed(-40);
		m_spring2->SetMotorSpeed(-40);
		//std::cout << "Truck going right" << std::endl;
	}
	else if (core_input::InputSystem::isKeyHeld(KEYBOARD_KEY_A)){
		m_spring1->EnableMotor(true);
		m_spring2->EnableMotor(true);
		m_spring1->SetMotorSpeed(40);
		m_spring2->SetMotorSpeed(40);
	}
	else {
		m_spring1->SetMotorSpeed(-0.001);
		m_spring2->SetMotorSpeed(-0.001);

		m_spring1->EnableMotor(false);
		m_spring2->EnableMotor(false);
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


	if (core_input::InputSystem::isKeyHeld(KEYBOARD_KEY_P)) {
		Camera::getInstance()->setPosition(Camera::getInstance()->getPosition().x + 1.5f, Camera::getInstance()->getPosition().y);
	}
	else if (core_input::InputSystem::isKeyHeld(KEYBOARD_KEY_O)) {
		Camera::getInstance()->setPosition(Camera::getInstance()->getPosition().x - 1.5f, Camera::getInstance()->getPosition().y);
	}

	//core_renderer::Camera::getInstance()->setPosition(thisObject->getPosition().x, thisObject->getPosition().y + 5);

	// Set the wheel object positions
	Object::getObjectByName("Wheel1")->setPosition(m_wheel1->GetPosition());
	Object::getObjectByName("Wheel1")->setRotation(-m_wheel1->GetAngle());
	Object::getObjectByName("Wheel2")->setPosition(m_wheel2->GetPosition());
	Object::getObjectByName("Wheel2")->setRotation(-m_wheel1->GetAngle());
	Object::getObjectByName("Wheel3")->setPosition(m_wheel3->GetPosition());
	Object::getObjectByName("Wheel3")->setRotation(-m_wheel1->GetAngle());

	Object::getObjectByName("Wheel4")->setPosition(m_trailerWheel1->GetPosition());
	Object::getObjectByName("Wheel4")->setRotation(-m_trailerWheel1->GetAngle());
	Object::getObjectByName("Wheel5")->setPosition(m_trailerWheel2->GetPosition());
	Object::getObjectByName("Wheel5")->setRotation(-m_trailerWheel2->GetAngle());

	//((RenderComponent*)Object::getObjectByName("Wheel1")->getComponentScript("RenderComponent"))->setSize((1), (1));
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

	float mass1 = m_wheel1->GetMass() / 1.5f;
	float mass2 = m_wheel2->GetMass() / 1.5f ;
	float mass3 = m_wheel3->GetMass() / 1.5f;

	float hertz = 4.0f;
	float dampingRatio = 1.0f;
	float omega = 2.0f * b2_pi * hertz;

	jd.Initialize(m_truck, m_wheel1, m_wheel1->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 20.0f; // 20
	jd.enableMotor = true;
	jd.stiffness = mass1 * omega * omega;
	jd.damping = 2.0f * mass1 * dampingRatio * omega;
	jd.lowerTranslation = -0.25f;
	jd.upperTranslation = 0.25f;
	jd.enableLimit = true;
	m_spring1 = (b2WheelJoint*)core_physics::PhysicsSystem::getInstance()->getWorld()->CreateJoint(&jd);

	jd.Initialize(m_truck, m_wheel2, m_wheel2->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 20.0f; // 20
	jd.enableMotor = true;
	jd.stiffness = mass2 * omega * omega;
	jd.damping = 2.0f * mass2 * dampingRatio * omega;
	jd.lowerTranslation = -0.25f;
	jd.upperTranslation = 0.25f;
	jd.enableLimit = true;
	m_spring2 = (b2WheelJoint*)core_physics::PhysicsSystem::getInstance()->getWorld()->CreateJoint(&jd);

	jd.Initialize(m_truck, m_wheel3, m_wheel3->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 10.0f; // 10
	jd.enableMotor = false;
	jd.stiffness = mass3 * omega * omega;
	jd.damping = 2.0f * mass3 * dampingRatio * omega;
	jd.lowerTranslation = -0.25f;
	jd.upperTranslation = 0.25f;
	jd.enableLimit = true;
	m_spring3 = (b2WheelJoint*)core_physics::PhysicsSystem::getInstance()->getWorld()->CreateJoint(&jd);

	//Trailer
	{
		b2PolygonShape box;
		b2Vec2 vertices[8];
		vertices[0].Set(-9.0, 2.3f);
		vertices[1].Set(-1.7f, 2.3f);
		vertices[2].Set(-1.7f, 0.2f);
		vertices[3].Set(-9.0f, 0.2f);
		box.Set(vertices, 4);


		b2PolygonShape axle;
		vertices[0].Set(-8.5, 0.2f);
		vertices[1].Set(-6.0f, 0.2f);
		vertices[2].Set(-6.0f, -0.5f);
		vertices[3].Set(-8.5f, -0.5f);
		axle.Set(vertices, 4);

		b2CircleShape circle;
		circle.m_radius = 0.5f;

		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position.Set(0.0f, 1.0f);
		m_trailer = core_physics::PhysicsSystem::getInstance()->getWorld()->CreateBody(&bd);
		m_trailer->CreateFixture(&box, 1.0f);
		m_trailer->CreateFixture(&axle, 1.0f);

		b2RevoluteJointDef rjd;
		rjd.lowerAngle = -0.2f;
		rjd.upperAngle = 0.2f;
		rjd.enableLimit = true;
		b2Vec2 anchor(-1.7f, 0.25f);
		rjd.Initialize(m_truck, m_trailer, anchor);
		core_physics::PhysicsSystem::getInstance()->getWorld()->CreateJoint(&rjd);


		b2FixtureDef fd;
		fd.shape = &circle;
		fd.density = 1.0f;
		fd.friction = 0.9f;

		bd.position.Set(-6.5f, 0.35f);
		m_trailerWheel1 = core_physics::PhysicsSystem::getInstance()->getWorld()->CreateBody(&bd);
		m_trailerWheel1->CreateFixture(&fd);

		bd.position.Set(-8.0f, 0.35f);
		m_trailerWheel2 = core_physics::PhysicsSystem::getInstance()->getWorld()->CreateBody(&bd);
		m_trailerWheel2->CreateFixture(&fd);

		b2WheelJointDef jd;
		b2Vec2 axis(0.0f, 1.0f);

		float mass2 = m_trailerWheel1->GetMass();
		float mass3 = m_trailerWheel2->GetMass();

		float hertz = 4.0f;
		float dampingRatio = 0.7f;
		float omega = 2.0f * b2_pi * hertz;

		jd.Initialize(m_trailer, m_trailerWheel1, m_trailerWheel1->GetPosition(), axis);
		jd.motorSpeed = 0.0f;
		jd.maxMotorTorque = 20.0f;
		jd.enableMotor = false;
		jd.stiffness = mass2 * omega * omega;
		jd.damping = 2.0f * mass2 * dampingRatio * omega;
		jd.lowerTranslation = -0.25f;
		jd.upperTranslation = 0.25f;
		jd.enableLimit = true;
		m_trailerSpring1 = (b2WheelJoint*)core_physics::PhysicsSystem::getInstance()->getWorld()->CreateJoint(&jd);

		jd.Initialize(m_trailer, m_trailerWheel2, m_trailerWheel2->GetPosition(), axis);
		jd.motorSpeed = 0.0f;
		jd.maxMotorTorque = 10.0f;
		jd.enableMotor = false;
		jd.stiffness = mass3 * omega * omega;
		jd.damping = 2.0f * mass3 * dampingRatio * omega;
		jd.lowerTranslation = -0.25f;
		jd.upperTranslation = 0.25f;
		jd.enableLimit = true;
		m_trailerSpring2 = (b2WheelJoint*)core_physics::PhysicsSystem::getInstance()->getWorld()->CreateJoint(&jd);
	}
}

std::string TruckCabinComponent::getTypeString() {
	return "TruckCabinComponent";
}

TruckCabinComponent::~TruckCabinComponent() {

}