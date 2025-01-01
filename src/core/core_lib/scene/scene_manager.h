#pragma once

#include <memory>

#include "core_lib/scene/scene.h"

namespace sauna_scene
{

// TODO: Support for multiple scenes?
class SceneManager
{
public:
    void init();

    void setActiveScene(std::unique_ptr<sauna_scene::GameScene> scene);
    inline GameScene* getActiveScene() const { return m_activeScene.get(); }

    void updateActiveScene();
    void shutdown();

private:
    std::unique_ptr<GameScene> m_activeScene;
};

}; // namespace sauna_scene
