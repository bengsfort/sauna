#pragma once

#include "core_lib/scene/scene.h"

namespace sauna_game
{

using namespace sauna_scene;

class TestScene : public GameScene
{
public:
	inline TestScene() : GameScene() {}
	inline ~TestScene() {};

	virtual void init() override;
	virtual void update() override;
	virtual void drawScene() override;

private:
	int m_currTick = 0;
};

}; // namespace sauna_game
