#include "AudioClip.h"
#include "../console/Console.h"
#define MINIMP3_IMPLEMENTATION
#include "minimp3/minimp3.h"
#include "minimp3/minimp3_ex.h"
using namespace core_audio;

AudioClip::AudioClip(const char* path) {
	mp3dec_init(&m_mp3Dec);
	mp3dec_load(&m_mp3Dec, path, &m_clipInfo, NULL, NULL);

	m_clipSize = m_clipInfo.samples * sizeof(mp3d_sample_t);
	m_clipLength = m_clipSize / (m_clipInfo.avg_bitrate_kbps * 1024.0f);
	m_openALFormat = setOALFormat(m_clipChannels);

	alGenBuffers(1, &m_clipID);
	alBufferData(m_clipID, m_openALFormat, m_clipInfo.buffer, m_clipSize, m_clipSampleRate);

	Console::log("Generated new AudioClip. ID=" + std::to_string(m_clipID));
}

AudioClip::~AudioClip() {
	alDeleteBuffers(1, &m_clipID);
}

int AudioClip::getSampleRate() {
	return m_clipSampleRate;
}
int AudioClip::getChannelType() {
	return m_clipChannels;
}

float AudioClip::getClipLength() {
	return m_clipLength;
}

ALenum AudioClip::getOALFormat() {
	return m_openALFormat;
}
ALuint AudioClip::getClipID() {
	return m_clipID;
}

int AudioClip::getClipSize() {
	return m_clipSize;
}

mp3d_sample_t* AudioClip::getData() {
	return m_clipInfo.buffer;
}

ALenum AudioClip::setOALFormat(uint32_t channels) {
	switch (channels)
	{
	case 1:
		return AL_FORMAT_MONO16;
	case 2:
		return AL_FORMAT_STEREO16;
	}
	return 0;
}