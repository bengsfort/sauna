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

public:
    Actor(Scene* scene);
    virtual ~Actor();

    template<typename T, typename... Args>
    T* addComponent(Args&&... args);

    template<typename ComponentType>
    ComponentType* getComponent();

    virtual void update(float timeDelta) = 0;
};

}; // namespace sauna_scene
