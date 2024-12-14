#pragma once

#include "scene/scene.h"
#include "scene/actor.h"

namespace sauna_game
{

using namespace sauna_scene;

class TestActor : public Actor
{
public:
    TestActor(Scene* scene);
};

}; // namespace sauna_game