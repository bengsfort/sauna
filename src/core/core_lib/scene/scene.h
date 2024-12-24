#pragma once

namespace sauna_scene
{

// TODO: Need to figure out how to handle cameras. Defaulting to Camera3D for now.
class GameScene
{
public:
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void drawScene() = 0;

public:
    GameScene() = default;
    virtual ~GameScene() = default;
};

}; // namespace sauna_scene
