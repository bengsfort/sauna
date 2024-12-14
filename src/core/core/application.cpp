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
    return isRunning;
}

void Application::tick()
{
	if (!m_activeScene) {
		BeginDrawing();
		ClearBackground(BLACK);

		DrawText("No active scene", 16, 16, 20, LIGHTGRAY);

		EndDrawing();
		return;
	}

	// Update game state
	m_activeScene->update(0.0f);

	// Draw
	BeginDrawing();
	ClearBackground(BLACK);

	// TODO: Avoid indirection here?
	m_activeScene->draw(0.0f);

	EndDrawing();
}

void Application::shutdown()
{
	std::cout << "Application shutdown" << std::endl;

	if (m_activeScene)
	{
		m_activeScene->cleanup();
		m_activeScene.release();
	}

	// Cleanup
	CloseWindow();
}

Application::~Application()
{
	this->shutdown();
}
