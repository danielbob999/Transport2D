#pragma once
#include "../../core/objectsystem/Object.h"
#include "../../core/objectsystem/ComponentScript.h"
#include "../../core/Core.h"
using namespace core_objectsystem;

class TestCompScript : public ComponentScript {
private:
public:
	TestCompScript();
	~TestCompScript();

	void start();
	void update();
	void close();

	std::string getTypeString();
};
