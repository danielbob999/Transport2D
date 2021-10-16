#pragma once
#include "InputKeyDefs.h"
#include "../coresystem/CoreSystem.h"
#include "../physics/PhysicsSystem.h"
#include "../renderer/RenderSystem.h"
#include "InputKeyDefs.h"
#include "../renderer/SDLIncludes.h"
#include "imgui/imgui.h"

namespace core_input {
	class InputSystem : public CoreSystem {
	private:
		static InputSystem* s_instance;

		bool* m_keysHeldThisFrame;
		bool* m_keysDownThisFrame;
		bool* m_keysUpThisFrame;
		bool* m_keysHeldLastFrame;

		bool* m_keysDownLocker;
	public:
		InputSystem();
		~InputSystem();

		void start() override;
		void update(double) override;
		void render(double) override;
		void close() override;

		void logKeyboardAction(SDL_KeyboardEvent& event);

		static bool isKeyDown(int);
		static bool isKeyHeld(int);
		static bool isKeyUp(int);

		static InputSystem* getInstance();
	};
}
