#pragma once

namespace sauna_scene
{

class PhysicsComponent
{
public:
    virtual ~PhysicsComponent() = default;
    
    virtual inline void update(float timeDelta) {}
    virtual inline void fixedUpdate(float fixedTimeDelta) {}
};

}; // namespace sauna_scene