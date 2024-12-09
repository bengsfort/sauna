#include <iostream>

#include "./transform_test_scene.h"

using namespace sauna_game;

// TODO: The objects just fly away, but the transforms look to have the correct data...
// Something wrong with the transformation to the raylib structs?
TransformTestScene::TransformTestScene()
{}

TransformTestScene::~TransformTestScene()
{
	this->cleanup();
}

void TransformTestScene::setup()
{
	m_camera = { 0 };
    m_camera.position = { 0.0f, 10.0f, 10.0f };  // Camera position
    m_camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
    m_camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    m_camera.fovy = 45.0f;                                // Camera field-of-view Y
    m_camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

	// Setup entities
	// Floor
	m_transforms[0].setParent(&m_rootTransform);
	m_transforms[0].setLocalPosition({ 0.0f, 0.0f, 0.0f });
	m_transforms[0].setLocalScale({ 10.0f, 0.1f, 10.0f });
	m_entities[0] = {
		LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f)),
		GRAY
	};

	// Cube
	m_transforms[1].setParent(&m_rootTransform);
	m_transforms[1].setLocalPosition({ 0.0f, 1.0f, 0.0f });
	m_transforms[1].setLocalScale({ 1.0f, 1.0f, 1.0f });
	m_entities[1] = {
		LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f)),
		RED
	};

	// Smaller cube attached to cube
	m_transforms[2].setParent(&m_transforms[1]);
	m_transforms[2].setLocalPosition({ 0.0f, 1.0f, 0.0f });
	m_transforms[2].setLocalScale({ 0.5f, 0.5f, 0.5f });
	m_entities[2] = {
		LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f)),
		BLUE
	};

	// Sphere to the side of the cube
	m_transforms[3].setParent(&m_rootTransform);
	m_transforms[3].setLocalPosition({ 2.0f, 1.0f, 0.0f });
	m_transforms[3].setLocalScale({ 1.0f, 1.0f, 1.0f });
	m_entities[3] = {
		LoadModelFromMesh(GenMeshSphere(1.0f, 16, 16)),
		GREEN
	};

	// Sphere to the other side
	m_transforms[4].setParent(&m_rootTransform);
	m_transforms[4].setLocalPosition({ -2.0f, 1.0f, 0.0f });
	m_transforms[4].setLocalScale({ 1.0f, 1.0f, 1.0f });
	m_entities[4] = {
		LoadModelFromMesh(GenMeshSphere(1.0f, 16, 16)),
		YELLOW
	};
}

void TransformTestScene::update()
{
	// Update entities
	UpdateCamera(&m_camera, CAMERA_FREE);
	m_spin += 1.0f;
	m_rootTransform.setLocalRotation({ m_spin, { 0.0f, 1.0f, 0.0f } });
	m_transforms[1].setLocalRotation({ -m_spin, { 0.0f, 1.0f, 0.0f } });
	// std::cout << "Floor transform: " << m_transforms[0].toString() << std::endl;
}

void TransformTestScene::draw()
{
	BeginMode3D(m_camera);
	{
		for (int i = 0; i < MAX_ENTITIES; i++)
		{
			// m_entities[i].model.transform = MatrixMultiply(
			// 	m_entities[i].model.transform,
			// 	m_transforms[i].getLocalToWorldMatrix()
			// );
			m_entities[i].model.transform = m_transforms[i].getLocalToWorldMatrix();
			DrawModel(m_entities[i].model, { 0.0f, 0.0f, 0.0f }, 1.0f, m_entities[i].color);
			// std::cout << "Entity " << i << "model " << m_tr << std::endl;
		}

		DrawGrid(10, 1.0f);
	}
	EndMode3D();
}

void TransformTestScene::cleanup()
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		UnloadModel(m_entities[i].model);
	}
}
