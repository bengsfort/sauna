#include <iostream>
#include "raylib.h"

#include "core_lib/core/application.h"
#include "core_lib/core/logger.h"
#include "core_lib/core/resource_manager.h"
#include "core_lib/chrono/clock.h"
#include "core_lib/core/engine_diagnostics.h"

using namespace sauna_core;

Application::Application() : graphics(), sceneManager()
{}

void Application::init()
{
	Logger::Init();
	Logger::LogInfo("Application init");

	sauna_chrono::Clock::Init();
	ResourceManager::Init();
	auto &resources = ResourceManager::Get();
	EngineDiagnostics::setFrameData(&sauna_chrono::Clock::GetFrameDiagnostics());
	EngineDiagnostics::setResourceData(&resources.getDiagnostics());

	SetTargetFPS(144);
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
	sauna_chrono::Clock::Tick();
	// TODO: Consume input
	sceneManager.updateActiveScene();
	sauna_chrono::Clock::MarkUpdateDone();
	graphics.draw(sceneManager.getActiveScene());
	sauna_chrono::Clock::MarkDrawDone();
}

void Application::shutdown()
{
	std::cout << "Application::shutdown" << std::endl;
	this->cleanupCoreSystems();

	ResourceManager::Shutdown();
	sauna_chrono::Clock::Shutdown();
	Logger::Shutdown();
}

void Application::cleanupCoreSystems()
{
	graphics.shutdown();
	sceneManager.shutdown();
}

Application::~Application()
{
}
