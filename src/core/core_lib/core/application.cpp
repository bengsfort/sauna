#include <iostream>
#include "raylib.h"

#include "core_lib/core/application.h"

using namespace sauna_core;

Application::Application() : graphics(), sceneManager()
{}

void Application::init()
{
	std::cout << "Application init" << std::endl;

	SetTargetFPS(60);
	this->initCoreSystems();
}

void Application::initCoreSystems()
{
	graphics.init(m_gameTitle);
	sceneManager.init();
}

void Application::run()
{
	while(!WindowShouldClose())
	{
		this->update();
	}
}

void Application::update()
{
	// Consume input

	sceneManager.updateActiveScene();
	graphics.draw(sceneManager.getActiveScene());
}

void Application::shutdown()
{
	std::cout << "Application::shutdown" << std::endl;
	this->cleanupCoreSystems();
}

void Application::cleanupCoreSystems()
{
	graphics.shutdown();
	sceneManager.shutdown();
}

Application::~Application()
{
}
