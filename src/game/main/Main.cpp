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
	Object* obj = Object::createObject("StinkyObject", 0, 0);
	obj->addComponentScript(rndcmp);
}

int main() {
	Core::start(init);
}
