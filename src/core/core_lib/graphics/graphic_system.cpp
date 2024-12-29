#include <iostream>

#include "core_lib/graphics/graphic_system.h"
#include "core_lib/core/logger.h"

using namespace sauna_graphics;
using namespace sauna_core;

// TODO: Init from settings, or if none exist determine correct ones using raylib API's.
// ie. if no settings exist, set window size to fullscreen at screen width + height.
GraphicSystem::GraphicSystem() :
	m_windowWidth(DEFAULT_WINDOW_WIDTH),
	m_windowHeight(DEFAULT_WINDOW_HEIGHT)
{}

GraphicSystem::GraphicSystem(int winWidth, int winHeight) :
	m_windowWidth(winWidth),
	m_windowHeight(winHeight)
{}

GraphicSystem::~GraphicSystem()
{
	Logger::LogInfo("GraphicSystem getting destroyed");
}

void GraphicSystem::init(const char* windowTitle) const
{
	// TODO: Make flags configurable
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(m_windowWidth, m_windowHeight, windowTitle);
}

void GraphicSystem::shutdown()
{
	CloseWindow();
}

void GraphicSystem::draw(sauna_scene::GameScene* scene)
{
	BeginDrawing();
	ClearBackground(this->clearColor);

	if (scene == nullptr) {
		// TODO: Iterate over drawables.
		DrawText("No active scene!", m_windowWidth * 0.5f, m_windowHeight * 0.5f, 24, WHITE);
	} else {
		scene->drawScene();
	}

	DrawFPS(16.0f, m_windowHeight - 24.0f);
	EndDrawing();
}
