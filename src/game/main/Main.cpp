#include <iostream>
#include "../../core/core.h"
#include "../../core/console/Console.h"
#include "../../core/objectsystem/Object.h"
using namespace core_objectsystem;


void start() {
}

void update(double delta) {
}

void close() {
}

int main() {
	Core::start(start, update, close);
}
