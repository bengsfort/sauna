#pragma once

#include "core_lib/scene/scene.h"
#include "core_lib/scene/actor.h"

namespace sauna_game
{

using namespace sauna_scene;

class TestActor : public Actor
{
public:
    TestActor(Scene* scene);
};

}; // namespace sauna_game