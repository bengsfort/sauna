#pragma once

#include "raylib.h"
#include "scene/scene.h"

namespace sauna_game
{

class TransformTestScene : public sauna_scene::Scene
{
public:
	void initialize() override;
};

}; // namespace sauna_game
