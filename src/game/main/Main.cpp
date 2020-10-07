#include <iostream>
#include <string>
#include "../../core/core.h"
#include "../../core/console/Console.h"
#include "TestCompScript.h"
#include "../../core/objectsystem/ComponentScript.h"
#include "../../core/objectsystem/Object.h"
#include "../../core/objectsystem/AudioComponent.h"
#include "../../core/objectsystem/RenderComponent.h"
#include "../../core/audio/AudioClip.h"
#include "../../core/objectsystem/GroundBodyComponent.h"
#include "TruckCabinComponent.h"
using namespace core_audio;
using namespace core_objectsystem;

void initTerrain() {
	GroundBodyComponent* gbc = new GroundBodyComponent();
	gbc->setBodyOffset(b2Vec2(0, 0));

	Object* obj = Object::createObject("GroundObject", 0, 0);
	obj->addComponentScript(gbc);
}

void initTruck() {
	TruckCabinComponent* tcc = new TruckCabinComponent();
	tcc->setBodyOffset(b2Vec2(0.7, -1.2));

	RenderComponent* cabinRc = new RenderComponent();
	cabinRc->setColour(1, 1, 1);
	cabinRc->setShouldRender(true);
	cabinRc->setSize(4.1, 4.1 * 0.7852);
	cabinRc->setRenderPriority(1000);
	cabinRc->setOffset(b2Vec2(-0.55, 1.1));

	Texture cabinTex = Texture("res/textures/game/truck/cabin.png");
	cabinRc->setTexture(cabinTex);

	Object* obj = Object::createObject("TruckObject", 0, 6);
	obj->addComponentScript(tcc);
	obj->addComponentScript(cabinRc);

	Object* wheel1 = Object::createObject("Wheel1", 0, 1);
	Object* wheel2 = Object::createObject("Wheel2", 0, 2);
	Object* wheel3 = Object::createObject("Wheel3", 0, 3);

	Texture wheelTex = Texture("res/textures/game/truck/tyre.png");

	RenderComponent* w1rc = new RenderComponent();
	w1rc->setColour(1, 1, 1);
	w1rc->setSize(1, 1);
	w1rc->setShouldRender(true);
	w1rc->setRenderPriority(2000);
	w1rc->setTexture(wheelTex);
	w1rc->setOffset(b2Vec2(0, 0));

	RenderComponent* w2rc = new RenderComponent();
	w2rc->setColour(1, 1, 1);
	w2rc->setSize(1, 1);
	w2rc->setShouldRender(true);
	w2rc->setRenderPriority(2000);
	w2rc->setTexture(wheelTex);
	w2rc->setOffset(b2Vec2(0, 0));

	RenderComponent* w3rc = new RenderComponent();
	w3rc->setColour(1, 1, 1);
	w3rc->setSize(1, 1);
	w3rc->setShouldRender(true);
	w3rc->setRenderPriority(2000);
	w3rc->setTexture(wheelTex);
	w3rc->setOffset(b2Vec2(0, 0));

	wheel1->addComponentScript(w1rc);
	wheel2->addComponentScript(w2rc);
	wheel3->addComponentScript(w3rc);
}

void init() {
	initTerrain();
	initTruck();
}

int main() {
	Core::start(init);
}
