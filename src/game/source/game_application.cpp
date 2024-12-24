#include <iostream>
#include <memory>

#include "game_application.h"
#include "scenes/test_scene.h"

using namespace sauna_game;

GameApplication::GameApplication() : sauna_core::Application()
{}

GameApplication::~GameApplication()
{
}

void GameApplication::init()
{
	sauna_core::Application::init();
	this->loadInitialScene();
}

void GameApplication::shutdown()
{
	std::cout << "GameApplication::shutdown" << std::endl;
	sauna_core::Application::shutdown();
}

void GameApplication::loadInitialScene()
{
	auto initial = std::make_unique<TestScene>();
	sceneManager.setActiveScene(std::move(initial));
}
