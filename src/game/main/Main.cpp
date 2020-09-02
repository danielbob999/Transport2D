#include <iostream>
#include "../../core/core.h"
#include "../../core/console/Console.h"


void start() {
	Console::logError("Henlo you stinker");
}

void update(double delta) {
}

void close() {
}

int main() {
	Core::start(start, update, close);
}
