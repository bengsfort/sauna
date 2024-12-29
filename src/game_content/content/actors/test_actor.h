#pragma once

#include "core_lib/scene/actor.h"

namespace sauna_game
{

using namespace sauna_scene;

class TestActor : public Actor
{
public:
    TestActor();

	inline void update(float deltaTime) override {};
	inline void draw(float deltaTime) override {};
};

}; // namespace sauna_game
