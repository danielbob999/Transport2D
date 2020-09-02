#pragma once
#include <vector>
#include "coresystem/CoreSystem.h"
#include "console/Console.h"
#include "../../includes/GLFW/glfw3.h"

class Core {
private:
	const int VERSION_MAJOR = 1;
	const int VERSION_MINOR = 0;
	const int VERSION_PATCH = 0;

	static Core* s_instance;
	static void glfwErrorCallbackFn(int, const char*);
	
	bool m_shouldBeLooping;
	Console* m_console;
	GLFWwindow* m_window;
	std::vector<CoreSystem*> m_coreSystems;
	double m_runTime;

	enum CoreSystemLoopType {
		None,
		Start,
		Update,
		Render,
		Close
	};

	// Funtion pointers
	void (*startFn)();
	void (*updateFn)(double);
	void (*closeFn)();

	void run();
	void callLoop(const Core::CoreSystemLoopType&);
public:
	Core();
	~Core();

	double getRunTime();

	static void start(void (*sFn)(), void (*uFn)(double), void (*cFn)());
	static void stop();

	static Core* getInstance();
	static void getVersion(int*, int*, int*);
	static void registerCoreSystem(CoreSystem*, int);
};
