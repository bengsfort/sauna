#include "game_application.h"

using namespace sauna_game;

int main() {
	GameApplication app;

	app.init();
	app.run();
	app.shutdown();

	return 0;
}
