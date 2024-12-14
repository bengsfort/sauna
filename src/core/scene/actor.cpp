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

void Actor::update(float timeDelta)
{
    for (auto& component : m_components) {
        component->update(timeDelta);
    }
}