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
	cabinRc->setSize(4.5, 4.5 * 0.7852);
	cabinRc->setRenderPriority(1000);

	Texture cabinTex = Texture("res/textures/game/truck/cabin.png");
	cabinRc->setTexture(cabinTex);

	Object* obj = Object::createObject("TruckObject", 0, 6);
	obj->addComponentScript(tcc);
	obj->addComponentScript(cabinRc);

	Object::createObject("Wheel1", 0, 0);
	Object::createObject("Wheel2", 0, 0);
	Object::createObject("Wheel3", 0, 0);
}

void init() {
	initTerrain();
	initTruck();
}

int main() {
	Core::start(init);
}
