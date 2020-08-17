#include <iostream>
#include "../../core/core.h"
#include "../../core/console/Console.h"

#include "../../../includes/box2d/box2d.h"

b2World world(b2Vec2(0.0f, 0.0f));

void start() {
	b2Vec2 gravity(0.0f, -10.0f);
	world = b2World(gravity);
}

void update(double delta) {
	float timeStep = 1.0f / 60.0f;
	world.Step(timeStep, 6, 2);

	Console::log(std::to_string(world.GetGravity().x) + ", " + std::to_string(world.GetGravity().y));
}

void close() {
}

int main() {
	Core::start(start, update, close);
}
