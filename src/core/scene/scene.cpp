#include "raylib.h"
#include "scene/scene.h"
#include "scene/actor.h"
#include "scene/render_component_2d.h"
#include "scene/render_component_3d.h"

using namespace sauna_scene;

// Lifecycle methods -----------------------------------
void Scene::update(float deltaTime)
{
    for (auto& actor : m_actors)
    {
        actor->update(deltaTime);
    }

    // TODO: update physics system?
}

void Scene::draw(float deltaTime)
{
    UpdateCamera(&camera, CAMERA_ORBITAL);

	BeginDrawing();
	ClearBackground(clearColor);

	for (auto& component : m_render2dComponents)
	{
		component->draw(deltaTime);
	}

	BeginMode3D(this->camera);

	for (auto& component : m_render3dComponents)
	{
		component->draw(deltaTime);
	}

	EndMode3D();
	EndDrawing();
}

void Scene::cleanup()
{
    m_actors.clear();
    m_physicsComponents.clear();
    m_render2dComponents.clear();
    m_render3dComponents.clear();
}

Scene::~Scene()
{
    this->cleanup();
}
