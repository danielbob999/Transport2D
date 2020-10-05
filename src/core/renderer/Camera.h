#pragma once
#include "../../../includes/box2d/box2d.h"
//#include "../../../includes/GLEW/glew.h"
#include "GLIncludes.h"

namespace core_renderer {
	class Camera {
	private:
		static Camera* s_instance;

		b2Vec2 m_position;
		b2Vec2 m_screenSize;
		float m_zoomFactor;
		float m_backgroundColour[3];

	public:
		Camera(int sizeX, int sizeY);
		~Camera();

		b2Vec2& getPosition();
		void setPosition(float, float);
		float getZoomFactor();
		void setZoomFactor(float);
		float* getBackgroundColour();
		void setBackgroundColour(float r, float g, float b);
		b2Vec2& getScreenSize();
		void setScreenSize(int, int);

		static Camera* getInstance();
	};
}
