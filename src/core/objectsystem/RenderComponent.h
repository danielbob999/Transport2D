#pragma once
#include "ComponentScript.h"
#include <string>
#include "../renderer/Texture.h"
#include "../../../includes/box2d/box2d.h"
using namespace core_renderer;

namespace core_objectsystem {
	class RenderComponent : public ComponentScript {
	private:
		bool m_shouldRender;
		Texture m_texture;
		float m_colour[3];
		b2Vec2 m_size;
	public:
		RenderComponent();
		~RenderComponent();

		void start();
		void update();
		void close();
		std::string getTypeString();

		// Component functions
		bool getShouldRender();
		void setShouldRender(bool);

		float* getColour();
		void setColour(float, float, float);

		Texture& getTexture();
		void setTexture(Texture&);

		b2Vec2& getSize();
		void setSize(float, float);

		b2Vec2 getVertexWorldPosition(int);
	};
}