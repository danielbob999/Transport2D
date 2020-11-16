#pragma once
#include <vector>
#include <Windows.h>
#include "renderer/GLIncludes.h"
#include "coresystem/CoreSystem.h"
#include "console/Console.h"
#include "input/InputSystem.h"
#include "input/InputKeyDefs.h"
#include "renderer/RenderSystem.h"
#include "../../includes/imgui/imgui.h"
#include "../../includes/imgui/imgui_impl_glfw.h"
#include "../../includes/imgui/imgui_impl_opengl3.h"
#include "audio/AudioManager.h"
#include "physics/PhysicsSystem.h"
#include "../game/controls/ControlsDisplay.h"
using namespace core_input;
using namespace core_renderer;
using namespace core_audio;
using namespace core_physics;
class Core {
private:
	const static int VERSION_MAJOR = 1;
	const static int VERSION_MINOR = 2;

	static Core* s_instance;
	static void glfwErrorCallbackFn(int, const char*);
	static void glfwWindowResizeCallbackFn(GLFWwindow*, int, int);
	
	bool m_shouldBeLooping;
	GLFWwindow* m_window;
	double m_runTime;
	double m_lastFrameDelta;
	bool m_limitTo60FPS;

	Console* m_console;
	InputSystem* m_inputSystem;
	RenderSystem* m_renderSystem;
	AudioManager* m_audioManager;
	PhysicsSystem* m_physicsSystem;
	ControlsDisplay* m_controlsDisplay;

	// Funtion pointers
	void (*initFn)();

	void run();
	void callObjectLoop(int code);
	static bool checkForResourcesDir();
public:
	Core();
	~Core();

	double getRunTime();
	double getLastFrameDelta();

	void set60FpsLimitStatus(bool);
	bool get60FpsLimitStatus();

	static void start(void (*sFn)());
	static void stop();

	static Core* getInstance();
	static GLFWwindow* getWindow();
	static void getVersion(int*, int*);
};
