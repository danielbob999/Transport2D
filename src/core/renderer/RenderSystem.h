#pragma once
#include <string>
#include "../coresystem/CoreSystem.h"
#include "GLIncludes.h"
#include "Camera.h"
#include "Texture.h"
#include "imgui/imgui.h"

namespace core_renderer {
	class RenderSystem : public CoreSystem {
	private:
		static RenderSystem* s_instance;

		GLint m_shaderProgramId;
		Camera* m_camera;
		Texture m_defaultTexture;
		int m_itemsRenderedLastFrame;
		bool m_renderObjectOrigins;
		bool m_showUI;
		bool m_shouldRender;

		GLint compileAndLinkShader(const char*, const char*);
		std::string getShaderInfoMsg(const GLuint);

		// Render functions
		void renderComponents();
		void renderObjectOrigins();
	public:
		RenderSystem();
		~RenderSystem();

		void start() override;
		void update(double) override;
		void render(double) override;
		void close() override;

		int getRenderCountLastFrame();
		void setOriginRenderStatus(bool);
		bool getOriginRenderStatus();
		static b2Vec2 worldToScreenCoords(b2Vec2);
		bool getUIStatus();
		void setUIStatus(bool);
		bool getRenderStatus();
		void setRenderStatus(bool);

		static RenderSystem* getInstance();
		static Texture& getDefaultTexture();
	};
}
