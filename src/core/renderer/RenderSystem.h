#pragma once
#include <string>
#include "../coresystem/CoreSystem.h"
#include "../../../includes/GLEW/glew.h"
//#include "../../../includes/GLFW/glfw3.h"

namespace core_renderer {
	class RenderSystem : public CoreSystem {
	private:
		static RenderSystem* s_instance;

		GLint m_shaderProgramId;

		GLint compileAndLinkShader(const char*, const char*);
		std::string getShaderInfoMsg(const GLuint);
	public:
		RenderSystem();
		~RenderSystem();

		void start() override;
		void update(double) override;
		void render(double) override;
		void close() override;

		static RenderSystem* getInstance();
	};
}
