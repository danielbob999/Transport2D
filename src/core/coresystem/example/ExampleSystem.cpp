#include "ExampleSystem.h"
#include "../../console/Console.h"
#include "../../Core.h"

ExampleSystem* ExampleSystem::s_instance = nullptr;

ExampleSystem::ExampleSystem() {
	if (s_instance != nullptr) {
		// There is already an instance of this system.
		// It should be disposed of safely and this instance, should become the current one
	}

	// Make this instance the current one
	s_instance = this;
}

void ExampleSystem::start() {
}

void ExampleSystem::update(double delta) {
}

void ExampleSystem::render(double delta) {
}

void ExampleSystem::close() {
}

ExampleSystem* ExampleSystem::getInstance() {
	return s_instance;
}

ExampleSystem::~ExampleSystem() {

}