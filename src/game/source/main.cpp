#include <iostream>
#include <memory>

#include "core_lib/core/application.h"
#include "scenes/transform_test_scene.h"

using namespace sauna_core;
using namespace sauna_game;

int main() {
	Application app;
	app.init();

	auto scene = std::make_unique<TransformTestScene>();
	scene->initialize();

	while (app.isRunning()) {
		app.tick();
	}

	return 0;
}
