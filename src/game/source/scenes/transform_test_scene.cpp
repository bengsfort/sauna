#include <iostream>

#include "./transform_test_scene.h"
#include "../actors/test_actor.h"


using namespace sauna_game;

void TransformTestScene::initialize()
{
	// camera = { 0 };
    // camera.position = { 0.0f, 10.0f, 10.0f };  // Camera position
    // camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
    // camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    // camera.fovy = 45.0f;                                // Camera field-of-view Y
    // camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

	// addActor<TestActor>(this);
}

// void TransformTestScene::update()
// {
// 	// Update entities
// 	UpdateCamera(&m_camera, CAMERA_FREE);
// 	m_spin += 1.0f;
// 	m_rootTransform.setLocalRotation({ m_spin, { 0.0f, 1.0f, 0.0f } });
// 	m_transforms[1].setLocalRotation({ -m_spin, { 0.0f, 1.0f, 0.0f } });
// 	// std::cout << "Floor transform: " << m_transforms[0].toString() << std::endl;
// }

// void TransformTestScene::draw()
// {
// 	BeginMode3D(m_camera);
// 	{
// 		for (int i = 0; i < MAX_ENTITIES; i++)
// 		{
// 			// m_entities[i].model.transform = MatrixMultiply(
// 			// 	m_entities[i].model.transform,
// 			// 	m_transforms[i].getLocalToWorldMatrix()
// 			// );
// 			m_entities[i].model.transform = m_transforms[i].getLocalToWorldMatrix();
// 			DrawModel(m_entities[i].model, { 0.0f, 0.0f, 0.0f }, 1.0f, m_entities[i].color);
// 			// std::cout << "Entity " << i << "model " << m_tr << std::endl;
// 		}

// 		DrawGrid(10, 1.0f);
// 	}
// 	EndMode3D();
// }

// void TransformTestScene::cleanup()
// {
// 	for (int i = 0; i < MAX_ENTITIES; i++)
// 	{
// 		UnloadModel(m_entities[i].model);
// 	}
// }
