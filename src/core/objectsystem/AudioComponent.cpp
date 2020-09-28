#include "AudioComponent.h"
#include "../../core/console/Console.h"
using namespace core_objectsystem;

AudioComponent::AudioComponent() {
	ALenum error;
	m_audioVolume = 0.5f;
	m_audioPitch = 0.5f;
	m_audioPlaying = false;
	alGenSources(1, &m_audioSourceID);
	if ((error = alGetError()) != AL_NO_ERROR) {
		Console::logError("Failed to generate AudioComponent: " + error);
		return;
	}
	Console::log("Successfully generate AudioComponent. ID=" + std::to_string(m_audioSourceID));
}

AudioComponent::~AudioComponent() {
	alDeleteSources(1, &m_audioSourceID);
}

void AudioComponent::setAudioClip(AudioClip* clip) {
	m_audioClip = clip;
}

bool AudioComponent::clipIsSet() {
	if (m_audioClip == nullptr) {
		return false;
	}
	return true;
}

void AudioComponent::start() {

}
void AudioComponent::update() {

}
void AudioComponent::close() {

}
std::string AudioComponent::getTypeString() {
	return "AudioComponent";
}

void AudioComponent::pauseAudio() {
	m_audioPlaying = false;
	alSourcePause(m_audioSourceID);
}
bool AudioComponent::playAudio() {
	m_audioPlaying = true;
	if (clipIsSet()) {
		alSourcei(m_audioSourceID, AL_LOOPING, false);
		alSourcei(m_audioSourceID, AL_BUFFER, m_audioClip->getClipID());
		alSourcef(m_audioSourceID, AL_GAIN, m_audioVolume);
		alSourcef(m_audioSourceID, AL_PITCH, m_audioPitch);
		alSourcePlay(m_audioSourceID);
		return true;
	}
	return false;
}
void AudioComponent::stopAudio() {
	m_audioPlaying = false;
	alSourceStop(m_audioSourceID);
}

void AudioComponent::setVolume(float volume) {
	m_audioVolume = volume;
	alSourcef(m_audioSourceID, AL_GAIN, m_audioVolume);
}
float AudioComponent::getVolume() {
	return m_audioVolume;
}
void AudioComponent::setPitch(float pitch) {
	m_audioPitch = pitch;
	alSourcef(m_audioSourceID, AL_PITCH, m_audioPitch);
}
float AudioComponent::getPitch() {
	return m_audioPitch;
}