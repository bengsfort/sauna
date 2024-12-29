#include <string>

#include "raylib.h"
#include "core_lib/core/resource_manager.h"

#include "./test_scene.h"

namespace sauna_game
{

using namespace sauna_scene;

TestScene::TestScene() : GameScene()
{}

TestScene::~TestScene()
{
    m_workbench = nullptr;
    m_tree = nullptr;
    m_rock = nullptr;
}

void TestScene::init()
{
    auto& resources = sauna_core::ResourceManager::Get();
    m_workbench = &resources.getModel("workbench");
    m_tree = &resources.getModel("tree");
    m_rock = &resources.getModel("rock");

    m_camera.position = { 0.0f, 10.0f, -10.0f };
    m_camera.target = { 0.0f, 0.0f, 0.0f };
    m_camera.up = { 0.0f, 1.0f, 0.0f };
    m_camera.fovy = 60.0f;
    m_camera.projection = CAMERA_PERSPECTIVE;
}

void TestScene::update()
{
    m_currTick += 1;
}

void TestScene::drawScene()
{
    std::string label = "TestScene current tick: ";
    label +=  std::to_string(m_currTick);
    DrawText(label.c_str(), 16, 16, 20, WHITE);

    BeginMode3D(m_camera);
    UpdateCamera((Camera*)&m_camera, CAMERA_ORBITAL);
    DrawModel(*m_workbench, { 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);
    DrawModel(*m_tree, { -1.0f, 0.0f, 0.0f }, 1.0f, WHITE);
    DrawModel(*m_rock, { 1.0f, 0.0f, 0.0f }, 1.0f, WHITE);
    DrawGrid(10, 1.0f);
    EndMode3D();
}

}; // namespace sauna_game
