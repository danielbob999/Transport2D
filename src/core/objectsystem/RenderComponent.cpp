#include "RenderComponent.h"
#include "../renderer/RenderSystem.h"
#include "../../../includes/box2d/box2d.h"
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

std::string RenderComponent::getTypeString() {
	return "RenderComponent";
}

RenderComponent::~RenderComponent() {

}