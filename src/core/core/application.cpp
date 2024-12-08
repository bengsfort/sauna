#include <iostream>

#include "application.h"
#include "raylib.h"

using namespace sauna_core;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 450;

Application::Application() {}

void Application::init()
{
	std::cout << "Application init" << std::endl;

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sauna Engine");
	SetTargetFPS(60);
}

bool Application::isRunning() const
{
	bool isRunning = !WindowShouldClose();
	std::cout << "Is application running? " << isRunning << std::endl;
    return isRunning;
}

void Application::tick()
{
	// Update game state
	// TODO

	std::cout << "Application tick" << std::endl;

	// Draw
	BeginDrawing();
	ClearBackground(BLACK);

	DrawText("Hello world", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 20, LIGHTGRAY);

	EndDrawing();
}

void Application::shutdown()
{
	std::cout << "Application shutdown" << std::endl;

	// Cleanup
	CloseWindow();
}

Application::~Application()
{
	this->shutdown();
}
