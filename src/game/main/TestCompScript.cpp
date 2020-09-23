#include "TestCompScript.h"
#include "../../core/input/InputSystem.h"
#include "../../core/input/InputKeyDefs.h"
#include "../../core/console/Console.h"
#include "../../core/objectsystem/Object.h"
using namespace core_input;

TestCompScript::TestCompScript() {

}

void TestCompScript::start() {

}

void TestCompScript::update() {
	if (InputSystem::isKeyHeld(KEYBOARD_KEY_W)) {
		Object* obj = Object::getObjectByName("StinkyObject");
		b2Vec2 pos = obj->getPosition();

		obj->setPosition(pos.x, pos.y + (3 * Core::getInstance()->getLastFrameDelta()));
	}

	if (InputSystem::isKeyHeld(KEYBOARD_KEY_Q)) {
		Object* obj = Object::getObjectByName("StinkyObject");
		obj->setRotation(obj->getRotation() + (1.5 * Core::getInstance()->getLastFrameDelta()));
	}
}

void TestCompScript::close() {

}

std::string TestCompScript::getTypeString() {
	return "TestScriptString";
}

TestCompScript::~TestCompScript() {

}