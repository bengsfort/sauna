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

	// TODO: Iterate over drawables instead of pointer chasing a scene.
	if (scene != nullptr) {
		scene->drawScene();
	}

	/* ideal flow:
	
	begin3d(active camera)

	for drawable in 3d drawable collection

	draw( drawable )

	end3d

	begin2d

	*/

	EndDrawing();
}
