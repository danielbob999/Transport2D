#include <iostream>
#include <string>
#include "../../core/core.h"
#include "../../core/console/Console.h"

void init() {
	Console::log("Init function is fun");
}

int main() {
	Core::start(init);
}
