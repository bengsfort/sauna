#pragma once

namespace sauna_scene
{

class PhysicsComponent
{
public:
    virtual ~PhysicsComponent() = default;
    
    virtual void update(float timeDelta) {}
    virtual void fixedUpdate(float fixedTimeDelta) {}
};

}; // namespace sauna_scene