#pragma once

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
};

}; // namespace sauna_core
