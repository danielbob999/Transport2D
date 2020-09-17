#pragma once
#include "../../../includes/box2d/box2d.h"
#include "../../../includes/GLEW/glew.h"

namespace core_renderer {
	class Camera {
	private:
		static Camera* s_instance;

		b2Vec2 m_position;
		b2Vec2 m_screenSize;
		float m_zoomFactor;
		float m_defaultDisplayAreaWidth;
		float m_backgroundColour[3];

	public:
		Camera(int sizeX, int sizeY);
		~Camera();

		b2Vec2& getPosition();
		void setPosition(int, int);
		float getZoomFactor();
		void setZoomFactor(float);
		float getDefaultDisplayAreaWidth();
		void setDefaultDisplayAreaWidth(float);
		float* getBackgroundColour();
		void setBackgroundColour(float r, float g, float b);
		b2Vec2& getScreenSize();

		static Camera* getInstance();
	};
}
