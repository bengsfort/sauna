#include <iostream>
#include "core/application.h"
#include "scenes/transform_test_scene.h"

using namespace sauna_core;
using namespace sauna_game;

int main() {
	Application app;
	app.init();

	auto scene = new TransformTestScene();
	scene->setup();
	app.setActiveScene(scene);

	while (app.isRunning()) {
		app.tick();
	}

	return 0;
}
