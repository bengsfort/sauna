#pragma once

#include "core_lib/scene/scene.h"

namespace sauna_core
{

using namespace sauna_scene;

class Application
{
public:
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
};

}; // namespace sauna_core
