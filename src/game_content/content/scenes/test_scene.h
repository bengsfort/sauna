#pragma once

#include "core_lib/scene/scene.h"

namespace sauna_game
{

using namespace sauna_scene;

class TestScene : public GameScene
{
public:
	TestScene();
	~TestScene();

	virtual void init() override;
	virtual void update() override;
	virtual void drawScene() override;

private:
	int m_currTick = 0;
	Camera3D m_camera = { 0 };
	Model* m_workbench = nullptr;
	Model* m_tree = nullptr;
	Model* m_rock = nullptr;
};

}; // namespace sauna_game
