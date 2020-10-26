#pragma once
#include "../../core/objectsystem/DrawablePhysicsComponent.h"
#include "box2d/box2d.h"
#include <vector>
using namespace core_objectsystem;
class TruckCabinComponent : public DrawablePhysicsComponent {
private:
	b2Body* m_cabinBody;
	std::vector<b2Fixture*> m_cabinFixtures; // All fixtures in this vector use the b2PolygonShape
	float m_scale;
	b2Fixture* m_wheelFixtures[3];
	b2Body* m_wheels[3];
	b2WheelJoint* m_wheelJointSprings[3];


	b2Body* m_truck;
	b2Body* m_trailer;

	b2Body* m_wheel1;
	b2Body* m_wheel2;
	b2Body* m_wheel3;

	b2Body* m_trailerWheel1;
	b2Body* m_trailerWheel2;

	float m_speed;
	b2WheelJoint* m_spring1;
	b2WheelJoint* m_spring2;
	b2WheelJoint* m_spring3;
	b2WheelJoint* m_trailerSpring1;
	b2WheelJoint* m_trailerSpring2;
	int m_orientation;

	// Faux inventory system
	std::string m_invItemName;
	int m_invItemWeight;
public:
	TruckCabinComponent();
	~TruckCabinComponent();

	void start() override;
	void update() override;
	void close() override;

	void draw() override;
	void destory();
	void generate() override;

	std::string getInventoryItemName();
	int getInventoryItemAmount();

	void setInventoryItem(std::string, int);
	void swapTruckOrientation();

	std::string getTypeString() override;
};
