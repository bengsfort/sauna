#pragma once

namespace sauna_scene
{

class RenderComponent2D
{
public:
    virtual ~RenderComponent2D() = default;
    
    virtual inline void update(float timeDelta) {}
    virtual inline void draw(float timeDelta) {}
};

}; // namespace sauna_scene