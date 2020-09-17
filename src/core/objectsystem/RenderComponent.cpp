#include "RenderComponent.h"
#include "../renderer/RenderSystem.h"
#include "../../../includes/box2d/box2d.h"
#include "ComponentScript.h"
#include <cmath>
using namespace core_objectsystem;

RenderComponent::RenderComponent() {
	m_colour[0] = 0.0f;
	m_colour[1] = 0.0f;
	m_colour[2] = 0.0f;

	m_texture = RenderSystem::getDefaultTexture();
	m_shouldRender = true;
	m_size = b2Vec2(2, 2);
}

void RenderComponent::start() {

}

void RenderComponent::update() {
}

void RenderComponent::close() {

}

bool RenderComponent::getShouldRender() {
	return m_shouldRender;
}

void RenderComponent::setShouldRender(bool v) {
	m_shouldRender = v;
}

float* RenderComponent::getColour() {
	return m_colour;
}

void RenderComponent::setColour(float r, float g, float b) {
	m_colour[0] = r;
	m_colour[1] = g;
	m_colour[2] = b;
}

Texture& RenderComponent::getTexture() {
	return m_texture;
}

void RenderComponent::setTexture(Texture& tex) {
	m_texture = tex;
}

b2Vec2& RenderComponent::getSize() {
	return m_size;
}

void RenderComponent::setSize(float x, float y) {
	m_size = b2Vec2(x, y);
}

b2Vec2 RenderComponent::getVertexWorldPosition(int vertId) {
    if (vertId < 1 || vertId > 4) {
        return b2Vec2(0, 0);
    }

    b2Vec2 parentPos = getParent()->getPosition();
    float rotation = getParent()->getRotation();

    float bounds[4] = {
        ((parentPos.x) - (m_size.x / 2.0f)),
        ((parentPos.y) - (m_size.y / 2.0f)),
        m_size.x,
        m_size.y
    };

    if (vertId == 1) {
        b2Vec2 vertPos = b2Vec2(bounds[1] + bounds[2], bounds[1]);

        float x = parentPos.x + (vertPos.x - parentPos.x) * (float)cos(rotation) + (vertPos.y - parentPos.y) * (float)sin(rotation);
        float y = parentPos.y - (vertPos.x - parentPos.x) * (float)sin(rotation) + (vertPos.y - parentPos.y) * (float)cos(rotation);

        return b2Vec2(x, y);
    }

    if (vertId == 2) {
        b2Vec2 vertPos = b2Vec2(bounds[0] + bounds[2], bounds[1] - bounds[3]);

        float x = parentPos.x + (vertPos.x - parentPos.x) * (float)cos(rotation) + (vertPos.y - parentPos.y) * (float)sin(rotation);
        float y = parentPos.y - (vertPos.x - parentPos.x) * (float)sin(rotation) + (vertPos.y - parentPos.y) * (float)cos(rotation);

        return b2Vec2(x, y);
    }

    if (vertId == 3) {
        b2Vec2 vertPos = b2Vec2(bounds[0], bounds[1] - bounds[3]);

        float x = parentPos.x + (vertPos.x - parentPos.x) * (float)cos(rotation) + (vertPos.y - parentPos.y) * (float)sin(rotation);
        float y = parentPos.y - (vertPos.x - parentPos.x) * (float)sin(rotation) + (vertPos.y - parentPos.y) * (float)cos(rotation);

        return b2Vec2(x, y);
    }

    if (vertId == 4) {
        b2Vec2 vertPos = b2Vec2(bounds[0], bounds[1]);

        float x = parentPos.x + (vertPos.x - parentPos.x)
            * (float)cos(rotation) + (vertPos.y - parentPos.y)
            * (float)sin(rotation);

        float y = parentPos.y - (vertPos.x - parentPos.x)
            * (float)sin(rotation) + (vertPos.y - parentPos.y)
            * (float)cos(rotation);

        return b2Vec2(x, y);
    }

    return b2Vec2(-1, -1);
}
}

std::string RenderComponent::getTypeString() {
	return "RenderComponent";
}

RenderComponent::~RenderComponent() {

}