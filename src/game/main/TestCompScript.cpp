#include "TestCompScript.h"
#include "../../core/input/InputSystem.h"
#include "../../core/input/InputKeyDefs.h"
#include "../../core/console/Console.h"
#include "../../core/objectsystem/Object.h"
#include "../../core/renderer/Camera.h"
#include "../../core/objectsystem/AudioComponent.h"
using namespace core_input;

TestCompScript::TestCompScript() {

}

void TestCompScript::start() {

}

void TestCompScript::update() {
	if (InputSystem::isKeyDown(KEYBOARD_KEY_W)) {
		AudioComponent* lus = (AudioComponent*) Object::getObjectByName("CuntNugget")->getComponentScript("AudioComponent");
		lus->playAudio();
		Console::log("HENLO");
	}
}

void TestCompScript::close() {

}

std::string TestCompScript::getTypeString() {
	return "TestScriptString";
}

TestCompScript::~TestCompScript() {

}