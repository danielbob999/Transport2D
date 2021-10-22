#include "Core.h"
#include "coresystem/example/ExampleSystem.h"
#include "objectsystem/ComponentScript.h"
#include "objectsystem/Object.h"
#include "input/InputSystem.h"
#include "renderer/RenderSystem.h"
#include "renderer/Camera.h"
#include "renderer/SDLIncludes.h"

using namespace core_input;
using namespace core_objectsystem;

/* Static variables */
Core* Core::s_instance = nullptr;

/* Private functions */
void Core::run() {
    // Initialize SDL Video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Failed to initialize SDL video\n");
        return;
    }

    // Create main window
    m_window = SDL_CreateWindow("Transport 2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1152, 648, SDL_WINDOW_OPENGL);
    
    if (m_window == NULL) {
        fprintf(stderr, "Failed to create main window\n");
        SDL_Quit();
        return;
    }

    // Initialize rendering context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_context = SDL_GL_CreateContext(m_window);

    if (m_context == NULL) {
        fprintf(stderr, "Failed to create GL context\n");
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return;
    }

    SDL_GL_SetSwapInterval(0); // Don't use VSYNC

    // Initialize GL Extension Wrangler (GLEW)
    GLenum err;
    glewExperimental = GL_TRUE; // Please expose OpenGL 3.x+ interfaces
    err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Failed to init GLEW\n");
        SDL_GL_DeleteContext(m_context);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& imGuiIO = ImGui::GetIO(); (void)imGuiIO;
    imGuiIO.IniFilename = NULL;

    ImGui::StyleColorsLight();

    //ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplSDL2_InitForOpenGL(m_window, m_context);
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
    m_controlsDisplay->start();

    // Call the init function provided. This is where Objects/ComponentScripts should be created.
    initFn();

    // Call the start function provided in main
    callObjectLoop(0);

    SDL_Event e;

    while (m_shouldBeLooping) {
        double frameStartTime = SDL_GetTicks() / 1000.0f;

        // Start a new GUI frame here. ImGui cal be called from all update functions
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
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
        m_controlsDisplay->update(m_lastFrameDelta);
        m_console->update();

        // Render background colour
        float* backgroundColour = Camera::getInstance()->getBackgroundColour();
        glClearColor(backgroundColour[0], backgroundColour[1], backgroundColour[2], 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

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

        SDL_GL_SwapWindow(m_window);

        //Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                m_shouldBeLooping = false;
            }

            if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
                m_inputSystem->logKeyboardAction(e.key);
            }
        }

        m_lastFrameDelta = ((SDL_GetTicks() / 1000.0f) - m_runTime); // Get the time difference (in seconds) then convert to milliseconds (x 1000)
        m_runTime = SDL_GetTicks() / 1000.0f;

        if (m_limitTo60FPS) {
            double totalFrameTimeInMs = ((SDL_GetTicks() / 1000.0f) - frameStartTime);
            double sleepTime = (1000 / 60.0) - totalFrameTimeInMs;

            // Reset the sleep back to zero if some calculation weirdness has happened
            if (sleepTime < 0) {
                sleepTime = 0;
            }

            Sleep(sleepTime);
        }
    }

    /*
     ===================================
      Call all the Core Systems close functions here
     ===================================
    */
    m_inputSystem->close();
    m_renderSystem->close();
    m_audioManager->close();
    m_controlsDisplay->close();
    m_physicsSystem->close();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    //Destroy window
    SDL_DestroyWindow(m_window);

    //Quit SDL subsystems
    SDL_Quit();

    return;

    // ------------------------------------------------------------------
    // Old code below here
    //--------------------------------------------------------------------
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
    return SDL_GetTicks() / 1000.0f;
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

    Console::log("Starting Transport2D. v" + std::to_string(VERSION_MAJOR) + "." + std::to_string(VERSION_MINOR));

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
    getInstance()->m_controlsDisplay = new ControlsDisplay();
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

void Core::getVersion(int* major, int* minor) {
	*major = getInstance()->VERSION_MAJOR;
	*minor = getInstance()->VERSION_MINOR;
	return;
}

Core* Core::getInstance() {
	return s_instance;
}

SDL_Window* Core::getWindow() {
    if (getInstance() != nullptr) {
        return getInstance()->m_window;
    }
}

SDL_GLContext Core::getContext() {
    if (getInstance() != nullptr) {
        return getInstance()->m_context;
    }
}

Core::~Core() {

}