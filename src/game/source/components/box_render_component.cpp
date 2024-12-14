#include "./box_render_component.h"

namespace sauna_game
{

BoxRenderComponent::BoxRenderComponent(sauna_scene::Transform* transform, Vector3 size, Color color)
{
    RenderComponent3D();
    m_transform = transform;
    m_color = color;
    m_model = LoadModelFromMesh(GenMeshCube(size.x, size.y, size.z));
}

BoxRenderComponent::~BoxRenderComponent()
{
    m_transform = nullptr;
    UnloadModel(m_model);
}

void BoxRenderComponent::update(float timeDelta)
{
}

void BoxRenderComponent::draw(float timeDelta)
{
    m_model.transform = m_transform->getLocalToWorldMatrix();
    DrawModel(m_model, { 0.0f }, 1.0f, m_color);
}

}; // namespace sauna_game
