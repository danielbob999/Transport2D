#include "AudioClip.h"
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

}

AudioClip::~AudioClip() {

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