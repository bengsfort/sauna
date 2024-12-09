#pragma once

#include "raylib.h"
#include "core/scene.h"
#include "components/transform.h"

namespace sauna_game
{
const int MAX_ENTITIES = 5;

typedef struct Entity {
	Model model;
	Color color;
} Entity;

class TransformTestScene : public sauna_core::Scene
{
public:
	TransformTestScene();
	~TransformTestScene();

	void setup() override;
	void update() override;
	void draw() override;
	void cleanup() override;

private:
	Entity m_entities[MAX_ENTITIES];
	sauna_components::Transform m_transforms[MAX_ENTITIES];
	Camera3D m_camera;
	float m_spin = 1.0f;
};

}; // namespace sauna_game
