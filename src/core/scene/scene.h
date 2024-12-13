#pragma once

#include <vector>
#include <memory>
#include "raylib.h"

#include "scene/render_component_2d.h"
#include "scene/render_component_3d.h"
#include "scene/physics_component.h"
#include "scene/actor.h"

namespace sauna_scene
{

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

public:
    ~Scene();

    template<typename T, typename... Args>
    T* addPhysicsComponent(Args&&... args);

    template<typename T, typename... Args>
    T* addRenderComponent(Args&&... args);

    template<typename T, typename... Args>
    T* addActor(Args&&... args);

    void update(float deltaTime);
    void draw(float deltaTime);
    void cleanup();
};

}; // namespace sauna_scene
