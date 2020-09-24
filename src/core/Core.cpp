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

    ImGui::StyleColorsLight();

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    /* 
     ===================================
      Call all the Core Systems start functions here 
     ===================================
    */
    m_inputSystem->start();
    m_renderSystem->start();

    // Call the init function provided. This is where Objects/ComponentScripts should be created.
    initFn();

    // Call the start function provided in main
    callObjectLoop(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(m_window) && m_shouldBeLooping) {
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
        m_inputSystem->update(m_lastFrameDelta); // This must come after every other update

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

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(m_window);

        /* Poll for and process events */
        glfwPollEvents();

        m_lastFrameDelta = glfwGetTime() - m_runTime;
        m_runTime = glfwGetTime();
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

void Core::start(void (*iFn)()) {
	if (s_instance == nullptr) {
		s_instance = new Core();
	}

    /*
     ===================================
      Initialise all the Core Systems here
      ===================================
    */
    getInstance()->m_inputSystem = new InputSystem();
    getInstance()->m_renderSystem = new RenderSystem();
    getInstance()->initFn = iFn;

	getInstance()->m_shouldBeLooping = true;

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

GLFWwindow* Core::getWindow() {
    if (getInstance() != nullptr) {
        return getInstance()->m_window;
    }
}

Core::~Core() {

}