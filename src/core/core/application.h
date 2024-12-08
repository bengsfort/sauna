#pragma once

#include "core/scene.h"

namespace sauna_core
{

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

	inline void setActiveScene(Scene* scene) { m_activeScene = scene; };
	inline Scene* getActiveScene() const { return m_activeScene; };

private:
	Scene* m_activeScene;
};

}; // namespace sauna_core
