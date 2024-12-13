#include "raylib.h"
#include "scene/scene.h"

using namespace sauna_scene;

// Instance management ---------------------------------
template<typename T, typename... Args>
T* Scene::addPhysicsComponent(Args&&... args)
{
    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    m_physicsComponents.push_back(std::move(component));
    T* componentPtr = component.get();
    return componentPtr;
}

template<typename T, typename... Args>
T* Scene::addRenderComponent(Args&&... args)
{
    auto component = std::make_unique<T>(std::forward<Args>(args)...);

    if constexpr (std::is_base_of_v<RenderComponent2D, T>)
	{
        m_render2dComponents.push_back(std::move(component));
    } else if constexpr (std::is_base_of_v<RenderComponent3D, T>) {
        m_render3dComponents.push_back(std::move(component));
    }

    T* componentPtr = component.get();
    return componentPtr;
}

template<typename T, typename... Args>
T* Scene::addActor(Args&&... args)
{
    auto actor = std::make_unique<T>(std::forward<Args>(args)...);
    m_actors.push_back(std::move(actor));
    T* actorPtr = actor.get();
    return actorPtr;
}

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
