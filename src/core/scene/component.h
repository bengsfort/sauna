#pragma once

namespace sauna_scene
{

class Component
{
public:
    virtual ~Component() = default;
    virtual void update(float deltaTime) {}
};

}; // namespace sauna_scene