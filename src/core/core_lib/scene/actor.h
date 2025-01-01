#pragma once

#include <vector>
#include <memory>

#include "core_lib/scene/scene.h"
#include "core_lib/scene/component.h"
#include "core_lib/scene/transform.h"

namespace sauna_scene
{

class Actor
{
public:

private:

public:
    Actor() = default;
    virtual ~Actor() = default;

    virtual void update(float deltaTime) = 0;
    virtual void draw(float deltaTime) = 0;
};

}; // namespace sauna_scene
