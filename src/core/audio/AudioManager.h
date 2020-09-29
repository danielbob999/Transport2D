#pragma once
#include "../coresystem/CoreSystem.h"
#include "OpenAL/al.h"
#include "OpenAL/alc.h"

namespace core_audio {
	class AudioManager : public CoreSystem {
	private:
		ALuint m_listenerID;
		
		ALCcontext* m_context;
		ALCdevice* m_device;

		static AudioManager* s_instance;

	public:
		AudioManager();
		~AudioManager();

		static AudioManager* getInstance();

		virtual void start() override;
		virtual void update(double) override;
		virtual void render(double) override;
		virtual void close() override;
	};
}