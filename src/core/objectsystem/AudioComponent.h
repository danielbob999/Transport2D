#pragma once
#include "OpenAL/al.h"
#include "OpenAL/alc.h"
#include "ComponentScript.h"
#include "../audio/AudioClip.h"
using namespace core_audio;

namespace core_objectsystem {
	class AudioComponent : public ComponentScript{
	private:
		AudioClip* m_audioClip;

		ALuint m_audioSourceID;

		float m_audioPitch;
		float m_audioVolume;
		
		bool m_audioPlaying;

	public:
		AudioComponent();
		~AudioComponent();

		void setAudioClip(AudioClip*);
		bool clipIsSet();

		void start();
		void update();
		void close();
		
		void pauseAudio();
		bool playAudio();
		void stopAudio();

		void setVolume(float);
		float getVolume();
		void setPitch(float);
		float getPitch();

		std::string getTypeString();

	};
}