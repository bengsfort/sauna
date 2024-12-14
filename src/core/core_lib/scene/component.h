#pragma once

namespace sauna_scene
{

class Component
{
public:
    virtual ~Component() = default;
    virtual inline void update(float deltaTime) {}
};

}; // namespace sauna_scene