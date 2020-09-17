#include "RenderSystem.h"
#include <vector>
#include <fstream>
#include "../objectsystem/ComponentScript.h"
#include "../objectsystem/Object.h"
#include "../console/Console.h"
#include "../Core.h"
#include "../objectsystem/RenderComponent.h"

using namespace core_renderer;
using namespace core_objectsystem;

RenderSystem* RenderSystem::s_instance = nullptr;

RenderSystem::RenderSystem() {
	if (s_instance != nullptr) {
		delete s_instance;
	}

	s_instance = this;

	Console::log("RenderSystem (" + Console::ptrToString(s_instance) + ") has been initialised");
}

void RenderSystem::start() {
	// Create a Camera
	int width, height;
	glfwGetWindowSize(Core::getWindow(), &width, &height);
	m_camera = new Camera(width, height);

	std::fstream fileStream;
	// Open the filestream and get the vertex source code from the file
	fileStream.open("res/shaders/vertex_shader.vs");
	std::string vSource = "";
	char nextChar;

	if (!fileStream.is_open()) {
		Console::logError("Failed to open 'res/shaders/vertex_shader.vs'");
	}

	while (fileStream.get(nextChar)) {
		vSource += nextChar;
	}

	fileStream.close();

	// Open the filestream and get the fragment source code from the file
	fileStream.open("res/shaders/fragment_shader.fs");
	std::string fSource = "";

	if (!fileStream.is_open()) {
		Console::logError("Failed to open 'res/shaders/fragment_shader.fsn'");
	}

	while (fileStream.get(nextChar)) {
		fSource += nextChar;
	}

	fileStream.close();

	m_shaderProgramId = compileAndLinkShader(vSource.c_str(), fSource.c_str());

	m_defaultTexture = Texture("res/textures/engine/default_texture.png");

	Console::log("RenderSystem (" + Console::ptrToString(this) + ") has successfully started");
}

void RenderSystem::update(double delta) {

}

void RenderSystem::render(double delta) {
	std::vector<Object*> objs = Object::getObjects();
	
	glEnable(GL_TEXTURE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_INDEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	for (int i = 0; i < objs.size(); i++) {
		if (i > 0) break;

		RenderComponent* renderComp = (RenderComponent*)objs[i]->getComponentScript("RenderComponent");

	}
}

void RenderSystem::close() {

}

GLint RenderSystem::compileAndLinkShader(const char* vertSource, const char* fragSource) {
	// Create and compile the vertex shader
	GLuint vertShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShaderId, 1, &vertSource, nullptr);
	glCompileShader(vertShaderId);
	std::string vertResStr = getShaderInfoMsg(vertShaderId);

	if (vertResStr != "") {
		Console::logError("Failed to compile vertex shader");
		Console::logError("Error: " + vertResStr);
	} else {
		Console::log("Successfully compiled vertex shader");
	}

	// Create and compile the fragment shader
	GLuint fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShaderId, 1, &fragSource, nullptr);
	glCompileShader(fragShaderId);
	std::string fragResStr = getShaderInfoMsg(fragShaderId);

	if (fragResStr != "") {
		Console::logError("Failed to compile fragment shader");
		Console::logError("Error: " + fragResStr);
	} else {
		Console::log("Successfully compiled fragment shader");
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertShaderId);
	glAttachShader(shaderProgram, fragShaderId);
	glLinkProgram(shaderProgram);
	glValidateProgram(shaderProgram);

	int result;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);

	if (result == GL_FALSE) {
		int length;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &length);
		char message[1024];
		glGetProgramInfoLog(shaderProgram, length, &length, message);

		Console::logError("Failed to link/validate shader program");
		Console::logError("Error " + std::string(message));

		glDeleteProgram(shaderProgram);
		return 0;
	} else {
		Console::log("Successfully linked and validated shader program");
	}

	glDeleteShader(vertShaderId);
	glDeleteShader(fragShaderId);

	return shaderProgram;
}

std::string RenderSystem::getShaderInfoMsg(const GLuint shaderId) {
	int result;
	std::string returnStr;

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		char message[1024] = "";
		glGetShaderInfoLog(shaderId, length, &length, message);
		returnStr = std::string(message);
	} else {
		returnStr = "";
	}

	return returnStr;
}

RenderSystem* RenderSystem::getInstance() {
	return s_instance;
}

Texture& RenderSystem::getDefaultTexture() {
	return getInstance()->m_defaultTexture;
}

RenderSystem::~RenderSystem() {
	glDeleteProgram(m_shaderProgramId);
}