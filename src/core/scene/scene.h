#pragma once

#include <vector>
#include <memory>
#include "raylib.h"

#include "scene/transform.h"
#include "scene/physics_component.h"
#include "scene/render_component_2d.h"
#include "scene/render_component_3d.h"

namespace sauna_scene
{

class Actor;
class PhysicsComponent;
class RenderComponent2D;
class RenderComponent3D;

// TODO: Need to figure out how to handle cameras. Defaulting to Camera3D for now.
class Scene
{
private:
    std::vector<std::unique_ptr<PhysicsComponent>> m_physicsComponents;
    std::vector<std::unique_ptr<RenderComponent2D>> m_render2dComponents;
    std::vector<std::unique_ptr<RenderComponent3D>> m_render3dComponents;
    std::vector<std::unique_ptr<Actor>> m_actors;

public:
	Color clearColor;
	Camera3D camera;
    Transform transform;

public:
    Scene() = default;
    ~Scene();

    inline virtual void initialize() {};

    // TODO: Get / Delete APIs
    template<typename T, typename... Args>
    T* addPhysicsComponent(Args&&... args)
    {
        auto component = std::make_unique<T, Args...>(std::forward<Args>(args)...);
        m_physicsComponents.push_back(std::move(component));
        T* componentPtr = component.get();
        return componentPtr;
    }

    template<typename T, typename... Args>
    T* addRenderComponent(Args&&... args)
    {
        auto component = std::make_unique<T, Args...>(std::forward<Args>(args)...);

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
    T* addActor(Args&&... args)
    {
        auto actor = std::make_unique<T, Args...>(std::forward<Args>(args)...);
        m_actors.push_back(std::move(actor));
        T* actorPtr = actor.get();
        return actorPtr;
    }

    void update(float deltaTime);
    void draw(float deltaTime);
    virtual void cleanup();
};

}; // namespace sauna_scene
