#include <iostream>
#include <string>
#include "../../core/core.h"
#include "../../core/console/Console.h"
#include "TestCompScript.h"
#include "../../core/objectsystem/ComponentScript.h"
#include "../../core/objectsystem/Object.h"
#include "../../core/objectsystem/RenderComponent.h"

void init() {
	Console::log("Init function is fun");

	// Main moving object
	Object* obj = Object::createObject("StinkyObject", 0, 0);
	RenderComponent* rndcmp = new RenderComponent();
	rndcmp->setShouldRender(true);
	rndcmp->setColour(1, 0, 0);
	rndcmp->setSize(4, 4);
	rndcmp->setRenderPriority(20);
	obj->addComponentScript(rndcmp);

	TestCompScript* ts = new TestCompScript();
	obj->addComponentScript(ts);

	// Green object
	Object* obj2 = Object::createObject("O1", -2, 5);

	RenderComponent* rnd = new RenderComponent();
	rnd->setShouldRender(true);
	rnd->setSize(4, 4);
	rnd->setColour(0, 1, 0);
	rnd->setRenderPriority(30); //  Should render over the top of the red

	obj2->addComponentScript(rnd);

	// Blue object
	Object* obj3 = Object::createObject("02", 4, -6);
	RenderComponent* rnd2 = new RenderComponent();
	rnd2->setColour(0, 0, 1);
	rnd2->setShouldRender(true);
	rnd2->setSize(4, 4);
	rnd2->setRenderPriority(10); //  Should render behind the red

	obj3->addComponentScript(rnd2);
}

int main() {
	Core::start(init);
}
