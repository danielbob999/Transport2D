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

	RenderComponent* rndcmp = new RenderComponent();
	rndcmp->setShouldRender(true);
	rndcmp->setColour(1, 0, 0);
	rndcmp->setSize(5, 5);
	Object* obj = Object::createObject("StinkyObject", 0, 0);

	TestCompScript* ts = new TestCompScript();
	obj->addComponentScript(ts);
	obj->addComponentScript(rndcmp);
}

int main() {
	Core::start(init);
}
