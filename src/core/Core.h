#pragma once
#include <vector>
#include "coresystem/CoreSystem.h"
#include "console/Console.h"
#include "../../includes/GLFW/glfw3.h"
#include "input/InputSystem.h"
#include "input/InputKeyDefs.h"
using namespace core_input;

class Core {
private:
	const int VERSION_MAJOR = 1;
	const int VERSION_MINOR = 0;
	const int VERSION_PATCH = 0;

	static Core* s_instance;
	static void glfwErrorCallbackFn(int, const char*);
	
	bool m_shouldBeLooping;
	GLFWwindow* m_window;
	double m_runTime;

	Console* m_console;
	InputSystem* m_inputSystem;

	// Funtion pointers
	void (*initFn)();

	void run();
	void callObjectLoop(int code);
public:
	Core();
	~Core();

	double getRunTime();

	static void start(void (*sFn)());
	static void stop();

	static Core* getInstance();
	static void getVersion(int*, int*, int*);
	static void registerCoreSystem(CoreSystem*, int);
};
