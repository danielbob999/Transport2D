#include <iostream>
#include <string>
#include "../../core/core.h"
#include "../../core/console/Console.h"
#include "TestCompScript.h"
#include "../../core/objectsystem/ComponentScript.h"
#include "../../core/objectsystem/Object.h"
#include "../../core/objectsystem/RenderComponent.h"
#include "../../core/audio/AudioClip.h"
using namespace core_audio;
void init() {
	AudioClip ac = AudioClip("res/audio/GameSong1.mp3");
	Console::log(std::to_string(ac.getClipID()));
}

int main() {
	Core::start(init);
}
