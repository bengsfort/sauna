#pragma once

#include <vector>
#include <memory>

#include "scene/scene.h"
#include "scene/component.h"
#include "scene/transform.h"

namespace sauna_scene
{

class Actor
{
public:
    Transform transform;

private:
    Scene* m_scene;
    std::vector<std::unique_ptr<Component>> m_components;

    template<typename T>
    struct always_false : std::false_type {};

public:
    Actor(Scene* scene);
    virtual ~Actor();

    template<typename T, typename... Args>
    T* addComponent(Args&&... args)
    {
        if constexpr (std::is_base_of_v<PhysicsComponent, T>) {
            return this->m_scene->addPhysicsComponent<T, Args...>(std::forward<Args>(args)...);
        } else if constexpr (std::is_base_of_v<RenderComponent3D, T> || std::is_base_of_v<RenderComponent2D, T>) {
            return this->m_scene->addRenderComponent<T, Args...>(std::forward<Args>(args)...);
        } else if constexpr (std::is_base_of_v<Component, T>) {
            auto component = std::make_unique<T, Args...>(std::forward<Args>(args)...);
            m_components.push_back(std::move(component));
            T* ptr = component.get();
            return ptr;
        } else {
            static_assert(always_false<T>::value, "Invalid component type");
        }
    }

    template<typename T>
    T* getComponent()
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

    virtual void update(float timeDelta) = 0;
};

}; // namespace sauna_scene
