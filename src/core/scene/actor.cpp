#include <type_traits>

#include "scene/actor.h"
#include "scene/physics_component.h"
#include "scene/render_component_2d.h"
#include "scene/render_component_3d.h"

using namespace sauna_scene;

Actor::Actor(Scene* scene) : m_scene(scene)
{}

Actor::~Actor()
{
    m_components.clear();
    m_scene = nullptr;
}

template<typename T, typename... Args>
T* Actor::addComponent(Args&&... args)
{
    if constexpr (std::is_base_of_v<PhysicsComponent, T>) {
        return m_scene->addPhysicsComponent<T>(std::forward<Args>(args)...);
    } else if constexpr (std::is_base_of_v<RenderComponent3D, T> || std::is_base_of_v<RenderComponent2D, T>) {
        return m_scene->addRenderComponent<T>(std::forward<Args>(args)...);
    }

    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    m_components.push_back(std::move(component));
    T* ptr = component.get();
    return ptr;
}

template<typename ComponentType>
ComponentType* Actor::getComponent()
{
    if constexpr (std::is_base_of_v<PhysicsComponent, T>) {
        // TODO
        return nullptr;
    } else if constexpr (std::is_base_of_v<RenderComponent3D, T> || std::is_base_of_v<RenderComponent2D, T>) {
        // TODO
        return nullptr;
    }

    for (auto& component : m_components) {
        if (T* casted = dynamic_cast<T*>(component.get())) {
            return casted;
        }
    }

    return nullptr;
}

void Actor::update(float timeDelta)
{
    for (auto& component : m_components) {
        component->update(timeDelta);
    }
}