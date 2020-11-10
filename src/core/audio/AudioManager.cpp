#include "AudioManager.h"
#include "../console/Console.h"
#include <exception>
#include <Windows.h>
using namespace core_audio;

AudioManager* AudioManager::s_instance = nullptr;

AudioManager::AudioManager() {
	if (s_instance != nullptr) {
		delete s_instance;
	}
	s_instance = this;

	/*
	m_device = alcOpenDevice(NULL);
	m_context = alcCreateContext(m_device, NULL);
	alcMakeContextCurrent(nullptr);

	ALCenum error = alcGetError(m_device);
	if (error != ALC_NO_ERROR) {
		Console::logError("Error when starting AudioManager. Context/Device Error");
	}

	const ALCchar* deviceName;
	deviceName = alcGetString(m_device, ALC_DEVICE_SPECIFIER);
	Console::log("AudioDevice name=" + std::string(deviceName));*/

	try {
		// create a default device
		ALCdevice* device = alcOpenDevice("");
		if (!device) {
			Console::logError("Could not create OpenAL device.");
			return;
		}

		// context attributes, 2 zeros to terminate 
		ALint attribs[6] = {
			0, 0
		};

		ALCcontext* context = alcCreateContext(device, attribs);
		if (!context) {
			Console::logError("Could not create OpenAL device.");
			alcCloseDevice(device);
			return;
		}

		if (!alcMakeContextCurrent(context)) {
			Console::logError("Could not create OpenAL device.");
			alcDestroyContext(context);
			alcCloseDevice(device);
			return;
		}

		Console::logError("[OpenAL] Version: " + std::string(alGetString(AL_VERSION)));
		Console::logError("[OpenAL] Vendor: " + std::string(alGetString(AL_VENDOR)));
		Console::logError("[OpenAL] Renderer: " + std::string(alGetString(AL_RENDERER)));

		Console::log("AudioManager (" + Console::ptrToString(s_instance) + ") has been initialised.");
	} catch (std::exception e) {
		MessageBox(nullptr, TEXT("Audio to load the AudioManager. This is normally caused by not having OpenAL installed."), TEXT("Error"), MB_OK);
	}
}
AudioManager::~AudioManager() {
	delete s_instance;
}

AudioManager* AudioManager::getInstance() {
	return s_instance;
}


void AudioManager::start() {
	alListenerf(AL_GAIN, 1.0f);
	alListener3f(AL_POSITION, 0, 0, 0);
	alListener3f(AL_VELOCITY, 0, 0, 0);

	Console::log("AudioManager (" + Console::ptrToString(s_instance) + ") has been started.");
}
void AudioManager::update(double delta) {

}
void AudioManager::render(double delta) {

}
void AudioManager::close() {
	alcDestroyContext(m_context);
	alcCloseDevice(m_device);
}