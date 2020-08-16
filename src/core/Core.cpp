#include "Core.h"
#include "coresystem/example/ExampleSystem.h"

/* Static variables */
Core* Core::s_instance = nullptr;

/* Private functions */
void Core::run() {
    /* Initialize the library */
    if (!glfwInit()) {
        return;
    }

    /* Create a windowed mode window and its OpenGL context */
    m_window = glfwCreateWindow(912, 513, "Transport2D", NULL, NULL);

    if (!m_window) {
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);

    // Loop through the core systems and call their start function
    callLoop(Core::CoreSystemLoopType::Start);

    // Call the start function provided in main
    startFn();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(m_window) && m_shouldBeLooping) {
        /* Run update functions here*/
        callLoop(Core::CoreSystemLoopType::Update);

        // Call the update function provided in main
        updateFn(getRunTime());

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Run render functions here */
        callLoop(Core::CoreSystemLoopType::Render);

        /* Swap front and back buffers */
        glfwSwapBuffers(m_window);

        /* Poll for and process events */
        glfwPollEvents();

        m_runTime = glfwGetTime();
    }

    // Call the close function provided in main
    // This must be done before all the important systems close down
    closeFn();

    callLoop(Core::CoreSystemLoopType::Close);

    glfwTerminate();

}

void Core::callLoop(const Core::CoreSystemLoopType& id) {
    std::vector<CoreSystem*>::iterator it = m_coreSystems.begin();

    while (it != m_coreSystems.end()) {

        switch (id) {
            case Core::CoreSystemLoopType::Start:
                (*it)->start();
                break;
            case Core::CoreSystemLoopType::Update:
                (*it)->update(glfwGetTime() - m_runTime);
                break;
            case Core::CoreSystemLoopType::Render:
                (*it)->render(glfwGetTime() - m_runTime);
                break;
            case Core::CoreSystemLoopType::Close:
                (*it)->close();
                break;
            default:
                break;
        }

        it++;
    }
}

/* Public functions */
Core::Core() {
	if (s_instance != nullptr) {
		// There is already an instance of Core somewhere, find it and kill it
		s_instance->stop();
	}

	s_instance = this;
	m_console = new Console();
}

double Core::getRunTime() {
    return m_runTime;
}

void Core::start(void (*sFn)(), void (*uFn)(double), void (*cFn)()) {
	if (s_instance == nullptr) {
		s_instance = new Core();
	}

    getInstance()->startFn = sFn;
    getInstance()->updateFn = uFn;
    getInstance()->closeFn = cFn;

	getInstance()->m_shouldBeLooping = true;

    /* REGISTER CORE SYSTEMS HERE */
    registerCoreSystem(new ExampleSystem(), 1);

	getInstance()->run();
}

void Core::stop() {
	getInstance()->m_shouldBeLooping = false;
}

void Core::getVersion(int* major, int* minor, int* patch) {
	*major = getInstance()->VERSION_MAJOR;
	*minor = getInstance()->VERSION_MINOR;
	*patch = getInstance()->VERSION_PATCH;
	return;
}

Core* Core::getInstance() {
	return s_instance;
}

void Core::registerCoreSystem(CoreSystem* system, int indx = 10) {
    getInstance()->m_coreSystems.push_back(system);

    Console::log("Registered new CoreSystem");
}

Core::~Core() {

}