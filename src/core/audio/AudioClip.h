#pragma once
#include "minimp3/minimp3.h"
#include "minimp3/minimp3_ex.h"
#include "OpenAL/al.h"
#include "OpenAL/alc.h"

namespace core_audio {
	class AudioClip {
	private:
		int m_clipSampleRate;
		int m_clipChannels;

		float m_clipLength;

		ALenum m_openALFormat;
		ALuint m_clipID;

		mp3dec_t m_mp3Dec;
		mp3dec_file_info_t m_clipInfo;
		uint32_t m_clipSize;

		ALenum setOALFormat(uint32_t);

	public:
		AudioClip(const char*);
		~AudioClip();

		int getSampleRate();
		int getChannelType();
		
		float getClipLength();

		ALenum getOALFormat();
		ALuint getClipID();
		int getClipSize();
		mp3d_sample_t* getData();
	};
}
