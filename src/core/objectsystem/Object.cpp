#include "Object.h"
#include "../console/Console.h"
#include <sstream>
#include <string>
#include "../../../includes/box2d/box2d.h"
#include "ComponentScript.h"
using namespace core_objectsystem;

/* Static variables */
int Object::s_nextId = 0;
std::vector<Object*> Object::s_objects = std::vector<Object*>();

Object::Object() {
	m_active = true;
	m_shouldRender = true;
	m_id = -1;
	m_name = "NULL";
	m_position = b2Vec2(0, 0);
}

ComponentScript* Object::addComponentScript(ComponentScript* script) {
	ComponentScript* currentScriptOfType = getComponentScript(script->getTypeString());

	if (currentScriptOfType == nullptr) {
		script->setParentId(m_id);
		m_components.push_back(script);
		return script;
	}

	return currentScriptOfType;
}

ComponentScript* Object::getComponentScript(const std::string& typeString) {
	std::vector<ComponentScript*>::iterator it = m_components.begin();

	while (it != m_components.end()) {
		if ((*it)->getTypeString() == typeString) {
			return (*it);
		}

		it++;
	}

	return nullptr;
}

void Object::removeComponentScript(const std::string& typeString) {
	std::vector<ComponentScript*>::iterator it = m_components.begin();

	while (it != m_components.end()) {
		if ((*it)->getTypeString() == typeString) {
			m_components.erase(it);
		}

		it++;
	}
}

Object* Object::createObject() {
	return createObject("NULL", 0, 0);
}

Object* Object::createObject(const std::string& name, int x, int y) {
	std::string fName = name;
	int fId = s_nextId; // Set the Objects id to the next available id

	if (name == "NULL") {
		fName = "Object (" + std::to_string(fId) + ")";
	}

	Object* obj = new Object();
	obj->setName(fName);
	obj->m_id = fId;
	obj->setPosition(x, y);
	obj->setActiveStatus(true);
	obj->setShouldRenderStatus(true);

	s_nextId++; // Increment the id so no Object ever has the same id

	// Use a hacky way to convert the pointer address to a string. hehe
	std::stringstream ss;
	ss << obj;

	Console::log("Created new Object. name='" + obj->getName() + "', id=" + std::to_string(obj->getId()) + ", address=" + ss.str());
	s_objects.push_back(obj);

	return obj;
}

void Object::runComponentFn(int code) {
	std::vector<ComponentScript*>::iterator it = m_components.begin();

	while (it != m_components.end()) {
		switch (code) {
			case 0:
				(*it)->start();
				break;
			case 1:
				(*it)->update();
				break;
			case 2:
				(*it)->close();
				break;
			default:
				break;
		}

		it++;
	}
}

std::vector<Object*>& Object::getObjects() {
	return s_objects;
}

b2Vec2& Object::getPosition() {
	return m_position;
}

void Object::setPosition(float x, float y) {
	setPosition(b2Vec2(x, y));
}

void Object::setPosition(const b2Vec2& vec) {
	m_position.x = vec.x;
	m_position.y = vec.y;
}

float Object::getRotation() {
	return m_rotation;
}

void Object::setRotation(float r) {
	m_rotation = r;
}

void Object::setActiveStatus(bool v) {
	m_active = v;
}

bool Object::getActiveStatus() {
	return m_active;
}

void Object::setShouldRenderStatus(bool v) {
	m_shouldRender = v;
}

bool Object::getShouldRenderStatus() {
	return m_shouldRender;
}

void Object::setName(std::string name) {
	m_name = name;
}

std::string& Object::getName() {
	return m_name;
}

int Object::getId() {
	return m_id;
}

Object* Object::getObjectByName(std::string n) {
	std::vector<Object*>::iterator it = s_objects.begin();

	while (it != s_objects.end()) {
		if ((*it)->m_name == n) {
			return (*it);
		}

		it++;
	}

	return nullptr;
}

Object* Object::getObjectById(int id) {
	std::vector<Object*>::iterator it = s_objects.begin();

	while (it != s_objects.end()) {
		if ((*it)->m_id == id) {
			return (*it);
		}

		it++;
	}

	return nullptr;
}

bool Object::equals(const Object* obj) {
	if (obj->m_id == m_id) {
		return true;
	}

	return false;
}

Object::~Object() {

}