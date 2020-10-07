#include "RenderSystem.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include "../objectsystem/ComponentScript.h"
#include "../objectsystem/Object.h"
#include "../console/Console.h"
#include "../Core.h"
#include "../objectsystem/RenderComponent.h"
#include "../physics/PhysicsSystem.h"
#include "../objectsystem/GroundBodyComponent.h"

using namespace core_renderer;
using namespace core_objectsystem;
using namespace core_physics;

RenderSystem* RenderSystem::s_instance = nullptr;

RenderSystem::RenderSystem() {
	if (s_instance != nullptr) {
		delete s_instance;
	}

	s_instance = this;
	m_shouldRender = true;

	Console::log("RenderSystem (" + Console::ptrToString(s_instance) + ") has been initialised");
}

void RenderSystem::start() {
	// Create a Camera
	int width, height;
	glfwGetWindowSize(Core::getWindow(), &width, &height);
	m_camera = new Camera(width, height);
	m_camera->setZoomFactor(24);

	m_showUI = true;
	m_renderObjectOrigins = true;

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
	if (m_showUI) {
		b2Vec2 screenSize = Camera::getInstance()->getScreenSize();
		ImGui::SetNextWindowPos(ImVec2(screenSize.x - 205, 30), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiCond_FirstUseEver);
		ImGui::Begin("Debug::Renderer");

		std::string s = "";
		s += "Frame Time: ";
		s += std::to_string(delta);
		s += "\nFPS: ";
		int fps = 1000 / delta;
		s += std::to_string(fps);
		ImGui::Text(s.c_str());
		ImGui::Checkbox("Render Components", &m_shouldRender);
		float tempZoom = Camera::getInstance()->getZoomFactor();
		ImGui::SliderFloat("Camera Zoom", &tempZoom, 0.1, 100);
		Camera::getInstance()->setZoomFactor(tempZoom);
		ImGui::End();
	}
}

void RenderSystem::render(double delta) {
	glEnable(GL_TEXTURE);
	glEnable(GL_BLEND);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_INDEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	if (m_shouldRender) {
		renderComponents();
	}

	// We need to disable blend so that the box2d rendering shows up
	glDisable(GL_BLEND);

	renderObjectOrigins();

}

void RenderSystem::renderComponents() {
	std::vector<Object*> objs = Object::getObjects();
	std::vector<RenderComponent*> renderComponents;

	// Loop through all Objects and get all the RenderComponents.
	//		Only add valid components that should be rendered (shouldRender() == true) to the vector
	for (int i = 0; i < objs.size(); i++) {
		RenderComponent* rc = (RenderComponent*)objs[i]->getComponentScript("RenderComponent");

		if (rc != nullptr) {
			if (rc->getShouldRender()) {
				renderComponents.push_back(rc);
			}
		}
	}

	// Sort the vector so that Objects are rendered based on their m_renderPriority
	std::sort(renderComponents.begin(), renderComponents.end(), [](RenderComponent* rhs, RenderComponent* lhs) { return rhs->getRenderPriority() < lhs->getRenderPriority(); });

	int itemsRendered = 0;

	for (int i = 0; i < renderComponents.size(); i++) {
		b2Vec2 renderSize = renderComponents[i]->getSize();
		float* renderColour = renderComponents[i]->getColour();
		Texture tex = renderComponents[i]->getTexture();

		float vertexData[32] = {
			worldToScreenCoords(renderComponents[i]->getVertexWorldPosition(1)).x,   worldToScreenCoords(renderComponents[i]->getVertexWorldPosition(1)).y,   1.0f,    renderColour[0],    renderColour[1],    renderColour[2],    1.0f, 0.0f,
			worldToScreenCoords(renderComponents[i]->getVertexWorldPosition(2)).x,   worldToScreenCoords(renderComponents[i]->getVertexWorldPosition(2)).y,   1.0f,    renderColour[0],    renderColour[1],    renderColour[2],    1.0f, 1.0f,
			worldToScreenCoords(renderComponents[i]->getVertexWorldPosition(3)).x,   worldToScreenCoords(renderComponents[i]->getVertexWorldPosition(3)).y,   1.0f,    renderColour[0],    renderColour[1],    renderColour[2],    0.0f, 1.0f,
			worldToScreenCoords(renderComponents[i]->getVertexWorldPosition(4)).x,   worldToScreenCoords(renderComponents[i]->getVertexWorldPosition(4)).y,   1.0f,    renderColour[0],    renderColour[1],    renderColour[2],    0.0f, 0.0f
		};


		int indiceData[6] = {
			0, 1, 3,
			1, 2, 3
		};

		GLuint vao, vbo, ebo;

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);

		// Bind the data to the vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 32, vertexData, GL_STATIC_DRAW);

		// Bind the data to the element buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 6, indiceData, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, tex.getId());

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.getWidth(), tex.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.getData());

		glUseProgram(m_shaderProgramId);
		glUniform1i(glGetUniformLocation(m_shaderProgramId, "ourTexture"), 0);

		glBindVertexArray(vao);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glDeleteBuffers(1, &ebo);
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);

		//delete[] vertexData;
		//delete[] indiceData;

		itemsRendered++;
	}

	m_itemsRenderedLastFrame = itemsRendered;
}

void RenderSystem::renderObjectOrigins() {
	glPointSize(5);

	if (m_renderObjectOrigins) {
		glBegin(GL_POINTS);

		std::vector<Object*> objects = Object::getObjects();

		for (int i = 0; i < objects.size(); i++) {
			glColor3b(0, 0, 0);
			glVertex2f(worldToScreenCoords(objects[i]->getPosition()).x, worldToScreenCoords(objects[i]->getPosition()).y);
		}

		glEnd();
	}
}

void RenderSystem::setUIStatus(bool v) {
	m_showUI = v;
}

bool RenderSystem::getUIStatus() {
	return m_showUI;
}

void RenderSystem::setOriginRenderStatus(bool v) {
	m_renderObjectOrigins = v;
}

bool RenderSystem::getOriginRenderStatus() {
	return m_renderObjectOrigins;
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

int RenderSystem::getRenderCountLastFrame() {
	return m_itemsRenderedLastFrame;
}

void RenderSystem::setRenderStatus(bool val) {
	m_shouldRender = val;
}

bool RenderSystem::getRenderStatus() {
	return m_shouldRender;
}

b2Vec2 RenderSystem::worldToScreenCoords(b2Vec2 worldPos) {
	b2Vec2 screenCoords = b2Vec2(0, 0);
	b2Vec2 cameraPos = Camera::getInstance()->getPosition();

	screenCoords.x = ((worldPos.x - cameraPos.x) / (Camera::getInstance()->getScreenSize().x / 2)) * Camera::getInstance()->getZoomFactor();
	screenCoords.y = ((worldPos.y - cameraPos.y) / (Camera::getInstance()->getScreenSize().y / 2)) * Camera::getInstance()->getZoomFactor();

	return screenCoords;
}

b2Vec2 RenderSystem::applyRotationScaleToPoint(b2Vec2 point, b2Vec2 origin, float rotationInRad, float scale) {
	float x = origin.x + (point.x - origin.x) * (float)cos(rotationInRad) + (point.y - origin.y) * (float)sin(rotationInRad);
	float y = origin.y - (point.x - origin.x) * (float)sin(rotationInRad) + (point.y - origin.y) * (float)cos(rotationInRad);

	//return b2Vec2(x / (Camera::getInstance()->getDefaultDisplayAreaWidth() / 2.0), y / (Camera::getInstance()->getDefaultDisplayAreaHeight() / 2.0));
	return b2Vec2(x * scale, y * scale);
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