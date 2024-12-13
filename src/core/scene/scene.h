#pragma once

#include <vector>
#include <memory>

#include "scene/render_component_2d.h"
#include "scene/render_component_3d.h"
#include "scene/physics_component.h"
#include "scene/actor.h"

namespace sauna_scene
{

class Scene
{
private:
    std::vector<std::unique_ptr<PhysicsComponent>> m_physicsComponents;
    std::vector<std::unique_ptr<RenderComponent2D>> m_render2dComponents;
    std::vector<std::unique_ptr<RenderComponent3D>> m_render3dComponents;
    std::vector<std::unique_ptr<Actor>> m_actors;

public:
    ~Scene();

    // TODO: Get / Delete APIs
    template<typename T, typename... Args>
    T* addPhysicsComponent(Args&&... args);

    template<typename T, typename... Args>
    T* addRenderComponent(Args&&... args);

    template<typename T, typename... Args>
    T* addActor(Args&&... args);

    void update(float deltaTime);
    void draw2d(float deltaTime);
    void draw3d(float deltaTime);
    void cleanup();
};

}; // namespace sauna_scene