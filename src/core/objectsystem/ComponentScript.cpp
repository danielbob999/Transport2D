#include "ComponentScript.h"
using namespace core_objectsystem;

int ComponentScript::getParentId() {
	return m_parentId;
}

void ComponentScript::setParentId(int id) {
	m_parentId = id;
}

