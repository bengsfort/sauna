#pragma once

namespace sauna_scene
{

class RenderComponent3D
{
public:
    virtual ~RenderComponent3D() = default;
    
    virtual inline void update(float timeDelta) {}
    virtual inline void draw(float timeDelta) {}
};

}; // namespace sauna_scene