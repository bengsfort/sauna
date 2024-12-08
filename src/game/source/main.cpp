#include <iostream>
#include "core/application.h"

using namespace sauna_core;

int main() {
	Application app;
	app.init();

	while (app.isRunning()) {
		app.tick();
	}

	return 0;
}
