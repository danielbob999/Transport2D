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
#include "../../game/missionsystem/MissionSystem.h"
using namespace core_audio;
using namespace core_objectsystem;

RenderComponent* generateRenderComponent(b2Vec2 size, b2Vec2 offset, bool shouldRender, float r, float g, float b, int priority, Texture tex) {
	RenderComponent* rendComp = new RenderComponent();
	rendComp->setSize(size.x, size.y);
	rendComp->setOffset(offset);
	rendComp->setShouldRender(shouldRender);
	rendComp->setColour(r, b, g);
	rendComp->setRenderPriority(priority);
	rendComp->setTexture(tex);
	return rendComp;
}

void initTerrain() {
	GroundBodyComponent* gbc = new GroundBodyComponent();
	gbc->setBodyOffset(b2Vec2(0, 0));

	Object* obj = Object::createObject("GroundObject", 0, 0);
	obj->addComponentScript(gbc);

	float totalWidth = 635;
	b2Vec2 offset = b2Vec2(-20, 0);

	Object* skyObj = Object::createObject("SkyObject", (totalWidth / 2) + offset.x, 25);
	RenderComponent* skyRend = generateRenderComponent(b2Vec2(totalWidth + 500, 60), b2Vec2(0, 0), true, 1, 1, 1, 500, Texture("res/textures/game/world/mapSky.png"));
	skyObj->addComponentScript(skyRend);
	
	Object* groundObj = Object::createObject("GroundRenderObject", (totalWidth / 2) - 7.5, 7.2);
	RenderComponent* grndRend = generateRenderComponent(b2Vec2((totalWidth + 113), (totalWidth + 115) * 0.1581), b2Vec2(0, 0), true, 1, 1, 1, 800, Texture("res/textures/game/world/mapGround.png"));
	groundObj->addComponentScript(grndRend);

	Object* cloudsObj = Object::createObject("CloudsObject", (totalWidth / 2) - 7.5, 3);
	RenderComponent* cldRnd = generateRenderComponent(b2Vec2((totalWidth + 113), (totalWidth + 115) * 0.1581), b2Vec2(0, 0), true, 1, 1, 1, 600, Texture("res/textures/game/world/mapClouds.png"));
	cloudsObj->addComponentScript(cldRnd);

	Object* grndbckObject = Object::createObject("GroundBackgroundObject", (totalWidth / 2) - 7.5, 7.2);
	RenderComponent* grndbkRend = generateRenderComponent(b2Vec2((totalWidth + 113), (totalWidth + 115) * 0.1581), b2Vec2(0, 0), true, 1, 1, 1, 700, Texture("res/textures/game/world/mapBackground.png"));
	grndbckObject->addComponentScript(grndbkRend);

	Object* grndfreObject = Object::createObject("GroundForegroundObject", (totalWidth / 2) - 7.5, 7.2);
	RenderComponent* grndfreRend = generateRenderComponent(b2Vec2((totalWidth + 113), (totalWidth + 115) * 0.1581), b2Vec2(0, 0), true, 1, 1, 1, 3000, Texture("res/textures/game/world/mapForeground.png"));
	grndfreObject->addComponentScript(grndfreRend);

	Object* mso = Object::createObject("MissionSystemObject", 0, 0);
	MissionSystem* ms = new MissionSystem();
	mso->addComponentScript(ms);
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

	Object* obj = Object::createObject("TruckObject", 0, 1);
	obj->addComponentScript(tcc);
	obj->addComponentScript(cabinRc);

	Object* wheel1 = Object::createObject("Wheel1", 0, 1);
	Object* wheel2 = Object::createObject("Wheel2", 0, 2);
	Object* wheel3 = Object::createObject("Wheel3", 0, 3);

	Texture wheelTex = Texture("res/textures/game/truck/mudTyre.png");

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

	Object* trailerWheel1 = Object::createObject("Wheel4", 0, 0);
	Object* trailerWheel2 = Object::createObject("Wheel5", 0, 0);

	RenderComponent* tw1rc = new RenderComponent();
	tw1rc->setColour(1, 1, 1);
	tw1rc->setSize(1, 1);
	tw1rc->setShouldRender(true);
	tw1rc->setRenderPriority(2000);
	tw1rc->setTexture(wheelTex);
	tw1rc->setOffset(b2Vec2(0, 0));

	RenderComponent* tw2rc = new RenderComponent();
	tw2rc->setColour(1, 1, 1);
	tw2rc->setSize(1, 1);
	tw2rc->setShouldRender(true);
	tw2rc->setRenderPriority(2000);
	tw2rc->setTexture(wheelTex);
	tw2rc->setOffset(b2Vec2(0, 0));

	trailerWheel1->addComponentScript(tw1rc);
	trailerWheel2->addComponentScript(tw2rc);

	Object* trailerObject = Object::createObject("TrailerObject", 0, 0);

	Texture trailerTex = Texture("res/textures/game/truck/trailer.png");

	RenderComponent* trailerRc = new RenderComponent();
	trailerRc->setColour(1, 1, 1);
	trailerRc->setShouldRender(true);
	trailerRc->setSize(7.5, 7.5 * 0.3843);
	trailerRc->setRenderPriority(1000);
	trailerRc->setOffset(b2Vec2(-5.35, 1));
	trailerRc->setTexture(trailerTex);

	trailerObject->addComponentScript(trailerRc);
}

void init() {
	initTerrain();
	initTruck();

	Object::createObject("MissionPointQuarry", 10, 6);
	Object::createObject("MissionPointMine", 360, -6);
	Object::createObject("MissionPointMill", 600, 6);
	Object::createObject("TrackSwitchPoint", 198, 6);
}

int main() {
	Core::start(init);
}
