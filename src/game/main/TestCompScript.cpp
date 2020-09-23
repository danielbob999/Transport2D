#include "TestCompScript.h"
#include "../../core/input/InputSystem.h"
#include "../../core/input/InputKeyDefs.h"
#include "../../core/console/Console.h"
#include "../../core/objectsystem/Object.h"
#include "../../core/renderer/Camera.h"
using namespace core_input;

TestCompScript::TestCompScript() {

}

void TestCompScript::start() {

}

void TestCompScript::update() {
	if (InputSystem::isKeyHeld(KEYBOARD_KEY_W)) {
		Object* obj = Object::getObjectByName("StinkyObject");
		b2Vec2 pos = obj->getPosition();
		pos.y += (2 * Core::getInstance()->getLastFrameDelta());
		obj->setPosition(pos.x, pos.y);
	}

	if (InputSystem::isKeyHeld(KEYBOARD_KEY_S)) {
		Object* obj = Object::getObjectByName("StinkyObject");
		b2Vec2 pos = obj->getPosition();
		pos.y -= (2 * Core::getInstance()->getLastFrameDelta());
		obj->setPosition(pos.x, pos.y);
	}

	if (InputSystem::isKeyHeld(KEYBOARD_KEY_A)) {
		Object* obj = Object::getObjectByName("StinkyObject");
		b2Vec2 pos = obj->getPosition();
		pos.x -= (2 * Core::getInstance()->getLastFrameDelta());
		obj->setPosition(pos.x, pos.y);
	}

	if (InputSystem::isKeyHeld(KEYBOARD_KEY_D)) {
		Object* obj = Object::getObjectByName("StinkyObject");
		b2Vec2 pos = obj->getPosition();
		pos.x += (2 * Core::getInstance()->getLastFrameDelta());
		obj->setPosition(pos.x, pos.y);
	}

	if (InputSystem::isKeyHeld(KEYBOARD_KEY_Q)) {
		Object* obj = Object::getObjectByName("StinkyObject");
		obj->setRotation(obj->getRotation() + (1.5 * Core::getInstance()->getLastFrameDelta()));
	}

	b2Vec2 thisPos = Object::getObjectById(this->getParentId())->getPosition();
	Camera::getInstance()->setPosition(thisPos.x, thisPos.y);
}

void TestCompScript::close() {

}

std::string TestCompScript::getTypeString() {
	return "TestScriptString";
}

TestCompScript::~TestCompScript() {

}