#include "core_lib/graphics/graphic_system.h"
#include <iostream>

using namespace sauna_graphics;

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
	std::cout << "Graphics shutdown" << std::endl;
	this->shutdown();
}

void GraphicSystem::init(const char* windowTitle)
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

	EndDrawing();
}
