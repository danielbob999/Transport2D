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
using namespace core_audio;
using namespace core_objectsystem;
void init() {
	AudioClip* ac = new AudioClip("res/audio/GameSong1.mp3");
	AudioComponent* acomp = new AudioComponent();
	acomp->setAudioClip(ac);

	TestCompScript* tcs = new TestCompScript();

	GroundBodyComponent* gcdd = new GroundBodyComponent();

	Object* obj = Object::createObject("CuntNugget", 0, 0);
	obj->addComponentScript(acomp);
	obj->addComponentScript(tcs);

	Object* ojb2 = Object::createObject("GroundObject", 0, 0);
	ojb2->addComponentScript(gcdd);
}

int main() {
	Core::start(init);
}
