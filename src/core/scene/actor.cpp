#include <type_traits>

#include "scene/actor.h"
#include "scene/physics_component.h"
#include "scene/render_component_2d.h"
#include "scene/render_component_3d.h"

using namespace sauna_scene;

template<typename T>
T* Actor::addComponent()
{
    if constexpr (std::is_base_of_v<PhysicsComponent, T>) {
        // addPhysicsComponent
    } else if constexpr (std::is_base_of_v<RenderComponent3D, T>) {
        // addRender3DComponent
    } else if constexpr (std::is_base_of_v<RenderComponent2D, T>) {
        // addRender2DComponent
    } else {
        // add normal component
    }

    // TODO
    return nullptr;
}

template<typename ComponentType>
ComponentType* Actor::getComponent()
{
    // TODO
    return nullptr;
}