#pragma once

namespace sauna_scene
{

class RenderComponent2D
{
public:
    virtual ~RenderComponent2D() = default;
    
    virtual void update(float timeDelta) {}
    virtual void draw(float timeDelta) {}
};

}; // namespace sauna_scene