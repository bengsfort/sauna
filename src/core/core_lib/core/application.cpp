#include <iostream>
#include "raylib.h"

#include "core_lib/core/application.h"

using namespace sauna_core;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 450;

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
    return isRunning;
}

void Application::tick()
{
	// Consume input

	// Update game state

	// Draw
	BeginDrawing();
	ClearBackground(BLACK);

	// Draw active scene

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
