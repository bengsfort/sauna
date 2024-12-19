#pragma once

#include <vector>
#include <string>

#include "raylib.h"
#include "core_lib/math/raylib_utils.h"

namespace sauna_scene
{

using namespace sauna_math;

class Transform
{
private:
	Transform* m_parent;
	std::vector<Transform*> m_children; // TODO: should this be list instead?

	Vector3 m_position;
	Vector3 m_scale;
	Vector3 m_origin;
	Quaternion m_rotation;

public:
	Transform();
	Transform(Vector3 position, RotationAxisAngle rotation, Vector3 scale);
	~Transform();

	// Hierarchy operations
	Transform* getParent() const;
	void setParent(Transform* parent);

	// State operations
	Vector3 getLocalPosition() const;
	Vector3 getWorldPosition() const;
	void setLocalPosition(Vector3 position);

	RotationAxisAngle getLocalRotation() const;
	RotationAxisAngle getWorldRotation() const;
	void setLocalRotation(RotationAxisAngle rotation);

	Vector3 getLocalScale() const;
	Vector3 getWorldScale() const;
	void setLocalScale(Vector3 scale);

	// Space transformations
	Matrix getLocalToWorldMatrix() const;
	Matrix getWorldToLocalMatrix() const;

	// Extractors
	static Vector3 extractPosition(const Matrix& matrix);
	static Matrix extractRotation(const Matrix& matrix);
	static Vector3 extractScale(const Matrix& matrix);

	// Utils
	std::string toString() const;

private:
	Matrix _makeLocalToParentMatrix() const;
	Matrix _makeParentToLocalMatrix() const;
};

}; // namespace sauna_components
