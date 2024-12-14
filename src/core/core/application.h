#pragma once

#include "scene/scene.h"

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

	inline void setActiveScene(std::unique_ptr<Scene> scene) { m_activeScene = std::move(scene); };
	// inline std::unique_ptr<Scene> getActiveScene() const { return m_activeScene; };

private:
	std::unique_ptr<Scene> m_activeScene;
};

}; // namespace sauna_core
