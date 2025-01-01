#pragma once

#include "core_lib/graphics/graphic_system.h"
#include "core_lib/scene/scene_manager.h"

namespace sauna_core
{

using namespace sauna_graphics;

class Application
{
public:
	GraphicSystem graphics;
	SceneManager sceneManager;

protected:
	const char* m_gameTitle = "Sauna Core";

public:
	Application();
	virtual ~Application();

	Application(const Application&) = delete; // Prevent copying
	Application& operator=(const Application&) = delete; // Prevent copy assignment

	virtual void init();
	virtual void run();
	virtual void shutdown();

protected:
	virtual void update();

private:
	void initCoreSystems();
	void cleanupCoreSystems();
};

}; // namespace sauna_core
