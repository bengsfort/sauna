#pragma once

namespace sauna_scene
{

class RenderComponent3D
{
public:
    virtual ~RenderComponent3D() = default;
    
    virtual void update(float timeDelta) {}
    virtual void draw(float timeDelta) {}
};

}; // namespace sauna_scene