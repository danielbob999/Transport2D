#include "AudioComponent.h"
#include "../../core/console/Console.h"
using namespace core_objectsystem;

AudioComponent::AudioComponent() {
	m_audioVolume = 0.5f;
	m_audioPitch = 0.0f;
	m_audioPlaying = false;
	alGenSources(1, &m_audioSourceID);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR) {
		Console::logError("Failed to generate AudioComponent: ");
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
		Console::log("CLIP IS SET!!!");
		alBufferData(m_audioClip->getClipID(), AL_FORMAT_MONO16, m_audioClip->getData(), m_audioClip->getClipSize(), m_audioClip->getSampleRate());
		alSourcei(m_audioSourceID, AL_BUFFER, m_audioClip->getClipID());
		alSourcei(m_audioSourceID, AL_LOOPING, false);
		alSourcef(m_audioSourceID, AL_GAIN, m_audioVolume);
		alSourcef(m_audioSourceID, AL_PITCH, m_audioPitch);
		ALint f;
		alGetSourcei(m_audioSourceID, AL_SOURCE_STATE, &f);

		Console::log("Source state before: " + std::to_string(f));

		alSourcePlay(m_audioSourceID);

		ALint d;
		alGetSourcei(m_audioSourceID, AL_SOURCE_STATE, &d);

		Console::log("Source state after: " + std::to_string(d));

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