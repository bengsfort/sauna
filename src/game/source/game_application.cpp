#include <iostream>
#include <memory>

#include "core_lib/core/resource_manager.h"
#include "game_application.h"
#include "content/scenes/test_scene.h"

using namespace sauna_game;

GameApplication::GameApplication() : sauna_core::Application(), m_gameTitle("Sauna Game")
{}

GameApplication::~GameApplication()
{
}

void GameApplication::init()
{
	sauna_core::Application::init();
	this->graphics.clearColor = DARKGRAY;
	this->loadResources();
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

void sauna_game::GameApplication::loadResources()
{
	auto& resources = sauna_core::ResourceManager::Get();
	resources.queueResources({
		{
			.name = "tree",
			.path = "models/tree_tall.glb",
			.type = sauna_core::ResourceType::Model,
			.scope = "global"
		},
		{
			.name = "rock",
			.path = "models/rock_a.glb",
			.type = sauna_core::ResourceType::Model,
			.scope = "global"
		},
		{
			.name = "workbench",
			.path = "models/workbench.glb",
			.type = sauna_core::ResourceType::Model,
			.scope = "global"
		}
		});
	resources.loadQueuedResources();
}
