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
    Actor();
    virtual ~Actor();

    virtual void update(float deltaTime);
    virtual void draw(float deltaTime);
};

}; // namespace sauna_scene
