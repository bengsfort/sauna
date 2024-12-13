#pragma once

<<<<<<< HEAD
#include <vector>
#include <memory>

#include "scene/scene.h"
#include "scene/component.h"
=======
#include "scene/transform.h"
>>>>>>> 5b30f9166fc12b9bc8f08d4579dcdeb4d10e8658

namespace sauna_scene
{

class Actor
{
private:
    Scene* m_scene;
    std::vector<std::unique_ptr<Component>> m_components;

public:
<<<<<<< HEAD
    Actor(Scene* scene);
    virtual ~Actor();
=======

public:
    Actor() {}
    virtual ~Actor() = default;
>>>>>>> 5b30f9166fc12b9bc8f08d4579dcdeb4d10e8658

    template<typename T, typename... Args>
    T* addComponent(Args&&... args);

    template<typename ComponentType>
    ComponentType* getComponent();

    virtual void update(float timeDelta) = 0;
};

}; // namespace sauna_scene
