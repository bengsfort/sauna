#include <string>
#include "raylib.h"
#include "./test_scene.h"

namespace sauna_game
{

using namespace sauna_scene;

void TestScene::init()
{
    // TODO: Init stuff here
}

void TestScene::update()
{
    m_currTick += 1;
}

void TestScene::drawScene()
{
    std::string label = "TestScene current tick: ";
    label +=  std::to_string(m_currTick);
    DrawText(label.c_str(), 16.0f, 16.0f, 20, WHITE);
}

}; // namespace sauna_game
