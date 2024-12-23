#include "game_application.h"
#include <iostream>

using namespace sauna_game;

GameApplication::GameApplication() : sauna_core::Application()
{}

GameApplication::~GameApplication()
{
}

void GameApplication::init()
{
	sauna_core::Application::init();
}

void GameApplication::shutdown()
{
	std::cout << "GameApplication::shutdown" << std::endl;
	sauna_core::Application::shutdown();
}
