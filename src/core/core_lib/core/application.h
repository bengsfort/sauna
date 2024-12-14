#pragma once

#include "core_lib/scene/scene.h"

namespace sauna_core
{

using namespace sauna_scene;

class Application
{
public:
	Application();
	~Application();

	Application(const Application&) = delete; // Prevent copying
	Application& operator=(const Application&) = delete; // Prevent copy assignment

	void init();
	bool isRunning() const;
	void tick();
	void shutdown();
};

}; // namespace sauna_core
