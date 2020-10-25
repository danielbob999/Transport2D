#include "Texture.h"
//#include "../../../includes/GLEW/glew.h"
#include "GLIncludes.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../../includes/stb_image/stb_image.h"
#include "../console/Console.h"
using namespace core_renderer;

Texture::Texture() {
	m_id = -1;
	m_data = nullptr;
	m_width = 0;
	m_height = 0;
	m_channels = 0;
}

Texture::Texture(const char* path) {
	m_data = stbi_load(path, &m_width, &m_height, &m_channels, 0);

	if (m_data == NULL) {
		m_data = nullptr;
		m_id = -1;

		Console::logError("Failed to generate Texture");
	} else {
		glGenTextures(1, (GLuint*)(&m_id));
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
		glGenerateMipmap(GL_TEXTURE_2D);

		Console::log("Generated new Texture. id=" + std::to_string(m_id));
	}
}

unsigned char* Texture::getData() {
	return m_data;
}

int Texture::getWidth() {
	return m_width;
}

int Texture::getHeight() {
	return m_height;
}

bool Texture::isValid() {
	if (m_id != -1 && m_data != nullptr) {
		return true;
	}

	return false;
}

int Texture::getId() {
	return m_id;
}

Texture::~Texture() {
	//stbi_image_free(m_data);
}