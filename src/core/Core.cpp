#include "Core.h"
#include "coresystem/example/ExampleSystem.h"
#include "objectsystem/ComponentScript.h"
#include "objectsystem/Object.h"
#include "input/InputSystem.h"
#include "renderer/RenderSystem.h"
#include "renderer/Camera.h"

using namespace core_input;
using namespace core_objectsystem;

/* Static variables */
Core* Core::s_instance = nullptr;

/* Static functions */
void Core::glfwErrorCallbackFn(int err, const char* msg) {
    // Log the error and close the app
    Console::logError("An GLFW error has occured (" + std::to_string(err) + "): " + std::string(msg));
    getInstance()->m_shouldBeLooping = false;
}

void Core::glfwWindowResizeCallbackFn(GLFWwindow* window, int width, int height) {
    Camera::getInstance()->setScreenSize(width, height);
}

/* Private functions */
void Core::run() {
    /* Initialize the library */
    if (!glfwInit()) {
        return;
    }

    // Specify glfw window hints
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    /* Create a windowed mode window and its OpenGL context */
    m_window = glfwCreateWindow(1152, 648, "Transport2D", NULL, NULL);

    if (!m_window) {
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);

    glfwSetKeyCallback(m_window, InputSystem::inputCallbackFn);
    glfwSetWindowSizeCallback(m_window, glfwWindowResizeCallbackFn);

    glewInit();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& imGuiIO = ImGui::GetIO(); (void)imGuiIO;
    imGuiIO.IniFilename = NULL;

    ImGui::StyleColorsLight();

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    /* 
     ===================================
      Call all the Core Systems start functions here 
     ===================================
    */
    m_inputSystem->start();
    m_physicsSystem->start();
    m_renderSystem->start();
	m_audioManager->start();

    // Call the init function provided. This is where Objects/ComponentScripts should be created.
    initFn();

    // Call the start function provided in main
    callObjectLoop(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(m_window) && m_shouldBeLooping) {
        double frameStartTime = glfwGetTime();

        // Start a new GUI frame here. ImGui cal be called from all update functions
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Call the update function of all ComponentScripts connected to Objects
        callObjectLoop(1);

        /*
         ===================================
          Call all the Core Systems update functions here
         ===================================
        */
        m_renderSystem->update(m_lastFrameDelta);
        m_physicsSystem->update(m_lastFrameDelta);
		m_audioManager->update(m_lastFrameDelta);
        m_inputSystem->update(m_lastFrameDelta); // This must come after every other update
        m_console->update();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Render background colour
        float* backgroundColour = Camera::getInstance()->getBackgroundColour();
        glClearColor(backgroundColour[0], backgroundColour[1], backgroundColour[2], 1.0f);

        /*
         ===================================
          Call all the Core Systems render functions here
         ===================================
        */
        m_inputSystem->render(m_lastFrameDelta);
        m_renderSystem->render(m_lastFrameDelta);
        m_physicsSystem->render(m_lastFrameDelta);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(m_window);

        /* Poll for and process events */
        glfwPollEvents();

        m_lastFrameDelta = (glfwGetTime() - m_runTime) * 1000; // Get the time difference (in seconds) then convert to milliseconds (x 1000)
        m_runTime = glfwGetTime();

		if (m_limitTo60FPS) {
			double totalFrameTimeInMs = (glfwGetTime() - frameStartTime) * 1000;
			double sleepTime = (1000 / 60.0) - totalFrameTimeInMs;

			// Reset the sleep back to zero if some calculation weirdness has happened
			if (sleepTime < 0) {
				sleepTime = 0;
			}

			Sleep(sleepTime);
		}
    }

    // Call the close function of all ComponentScripts
    // This must be done before all the important systems close down
    callObjectLoop(2);

    /*
     ===================================
      Call all the Core Systems close functions here
     ===================================
    */
    m_inputSystem->close();
    m_renderSystem->close();
	m_audioManager->close();
    m_physicsSystem->close();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();

}

void Core::callObjectLoop(int code) {
    std::vector<Object*> objs = Object::getObjects();
    std::vector<Object*>::iterator it = objs.begin();

    while (it != objs.end()) {
        (*it)->runComponentFn(code);
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

double Core::getLastFrameDelta() {
    return m_lastFrameDelta;
}

void Core::set60FpsLimitStatus(bool val) {
	m_limitTo60FPS = val;
}

bool Core::get60FpsLimitStatus() {
	return m_limitTo60FPS;
}

void Core::start(void (*iFn)()) {
	if (s_instance == nullptr) {
		s_instance = new Core();
	}

    /* Check if the resources folder exists */
    bool resExists = checkForResourcesDir();

    if (resExists == false) {
        // show windows popup
        MessageBox(nullptr, TEXT("Failed to load. Make sure the resources folder is in the same directory as this program."), TEXT("Error"), MB_OK);
        return;
    }

    /*
     ===================================
      Initialise all the Core Systems here
      ===================================
    */
    getInstance()->m_inputSystem = new InputSystem();
    getInstance()->m_renderSystem = new RenderSystem();
	getInstance()->m_audioManager = new AudioManager();
    getInstance()->m_physicsSystem = new PhysicsSystem();
    getInstance()->initFn = iFn;

	getInstance()->m_shouldBeLooping = true;

	getInstance()->run();
}

bool Core::checkForResourcesDir() {
    std::string path = "res";
    DWORD dwAttrib = GetFileAttributesA(path.c_str());

    if (dwAttrib == INVALID_FILE_ATTRIBUTES) {
        return false;
    }

    if (dwAttrib == FILE_ATTRIBUTE_DIRECTORY) {
        return true;
    }

    return false;
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

GLFWwindow* Core::getWindow() {
    if (getInstance() != nullptr) {
        return getInstance()->m_window;
    }
}

Core::~Core() {

}