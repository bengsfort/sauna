#pragma once

#include "raylib.h"
#include "core_lib/scene/transform.h"
#include "core_lib/scene/render_component_3d.h"

namespace sauna_game
{

using namespace sauna_scene;

class BoxRenderComponent : public RenderComponent3D
{
public:

private:
    Model m_model;
    sauna_scene::Transform* m_transform;
    Color m_color;

public:
    BoxRenderComponent(sauna_scene::Transform* transform, Vector3 size, Color color);
    ~BoxRenderComponent();

    void update(float timeDelta) override;
    void draw(float timeDelta) override;
};

}; // namespace sauna_game