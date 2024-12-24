#include "core_lib/scene/scene_manager.h"

using namespace std;
using namespace sauna_scene;

void SceneManager::init()
{
	// TODO: Implement
	m_activeScene = nullptr;
}

void SceneManager::shutdown()
{
	// TODO: Implement
	m_activeScene = nullptr;
}

void SceneManager::setActiveScene(unique_ptr<GameScene> scene)
{

	// TODO: Cleanup old scene? Multiple scenes?
	m_activeScene = std::move(scene);

	// TODO: Cleanup. Can use another unique_ptr to store the prev pointer,
	// and then delete/unload it async in a background thread.
}

void SceneManager::updateActiveScene()
{
	if (m_activeScene == nullptr) return;

	m_activeScene->update();
}


