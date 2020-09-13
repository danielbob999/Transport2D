#include <iostream>
#include <string>
#include "../../core/core.h"
#include "../../core/console/Console.h"
#include "TestCompScript.h"
#include "../../core/objectsystem/ComponentScript.h"
#include "../../core/objectsystem/Object.h"

void init() {
	Console::log("Init function is fun");

	TestCompScript* tcs = new TestCompScript();
	Object* obj = Object::createObject("StinkyObject", 0, 0);
	obj->addComponentScript(tcs);
}

int main() {
	Core::start(init);
}
