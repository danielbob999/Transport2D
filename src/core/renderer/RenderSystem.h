#pragma once
#include <string>
#include "../coresystem/CoreSystem.h"
#include "GLIncludes.h"
#include "Camera.h"
#include "Texture.h"

namespace core_renderer {
	class RenderSystem : public CoreSystem {
	private:
		static RenderSystem* s_instance;

		GLint m_shaderProgramId;
		Camera* m_camera;
		Texture m_defaultTexture;
		int m_itemsRenderedLastFrame;

		GLint compileAndLinkShader(const char*, const char*);
		std::string getShaderInfoMsg(const GLuint);
		b2Vec2 worldToScreenCoords(b2Vec2);
	public:
		RenderSystem();
		~RenderSystem();

		void start() override;
		void update(double) override;
		void render(double) override;
		void close() override;

		int getRenderCountLastFrame();

		static RenderSystem* getInstance();
		static Texture& getDefaultTexture();
	};
}
