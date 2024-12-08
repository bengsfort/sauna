#include <assert.h>
#include <iostream>

#include "transform.h"
#include "math/raylib_utils.h"

namespace sauna_components
{

Transform::Transform()
	: m_parent(nullptr)
	, m_position(Vector3Zero())
	, m_scale(Vector3One())
	, m_origin(Vector3Zero())
	, m_rotation(QuaternionIdentity())
{
}

Transform::Transform(Vector3 position, sauna_math::RotationAxisAngle rotation, Vector3 scale)
{
	setLocalPosition(position);
	setLocalScale(scale);
	setLocalRotation(rotation);
	m_parent = nullptr;
}

Transform::~Transform()
{
	std::cout << "Transform destroyed" << std::endl;

	// Clean up pointers
	for (auto child : m_children)
	{
		child->setParent(nullptr);
	}

	if (m_parent)
	{
		this->setParent(nullptr);
	}
}

// Hierarchy operations
Transform* Transform::getParent() const
{
	return m_parent;
}

void Transform::setParent(Transform* parent)
{
	// Remove from current parent
	if (m_parent)
	{
		// Remove from parent's children list
		for (auto it = m_parent->m_children.begin(); it != m_parent->m_children.end(); ++it)
		{
			if (*it == this)
			{
				m_parent->m_children.erase(it);
				break;
			}
		}
	}

	m_parent = parent;

	// Add to new parent
	if (m_parent)
	{
		m_parent->m_children.push_back(this);
	}
}

// State operations
Vector3 Transform::getLocalPosition() const
{
	return m_position;
}

Vector3 Transform::getWorldPosition() const
{
	auto worldMatrix = getLocalToWorldMatrix();
	return extractPosition(worldMatrix);
}

void Transform::setLocalPosition(Vector3 position)
{
	m_position = position;
}

RotationAxisAngle Transform::getLocalRotation() const
{
	Vector3 axis;
	float angle;
	QuaternionToAxisAngle(m_rotation, &axis, &angle);
	return { angle, axis * RAD2DEG };	// TODO: dont really like calculating and copying this always?
}

RotationAxisAngle Transform::getWorldRotation() const
{
	auto worldMatrix = getLocalToWorldMatrix();
	auto worldRotation = extractRotation(worldMatrix);

	// Make sure rotation is non-zero
	float matrixAngle = acos((worldRotation.m0 + worldRotation.m5 + worldRotation.m10 - 1) / 2);
	if (matrixAngle <= EPSILON && matrixAngle >= -EPSILON)
	{
		return { 0, Vector3Zero() };
	}

	// Get Quat from matrix
	Quaternion q = QuaternionFromMatrix(worldRotation);
	assert(!isnan(q.x) || !isnan(q.y) || !isnan(q.z) || !isnan(q.w));

	Vector3 axis;
	float angle;
	QuaternionToAxisAngle(q, &axis, &angle);
	return { angle, axis * RAD2DEG};
}

// Set rotation from an axis angle, angle expected to be in degrees.
void Transform::setLocalRotation(RotationAxisAngle rotation)
{
	m_rotation = QuaternionFromAxisAngle(rotation.axis, rotation.angle * DEG2RAD);
}

Vector3 Transform::getLocalScale() const
{
	return m_scale;
}

Vector3 Transform::getWorldScale() const
{
	auto worldMatrix = getLocalToWorldMatrix();
	return extractScale(worldMatrix);
}

void Transform::setLocalScale(Vector3 scale)
{
	m_scale = scale;
}

//  Space transformations
Matrix Transform::getLocalToWorldMatrix() const
{
	if (!m_parent)
	{
		return _makeLocalToParentMatrix();
	}

	// Get parent matrix
	auto parentMatrix = m_parent->getLocalToWorldMatrix();
	auto localMatrix = _makeLocalToParentMatrix();
	return MatrixMultiply(localMatrix, parentMatrix);
}

Matrix Transform::getWorldToLocalMatrix() const
{
	return MatrixInvert(getLocalToWorldMatrix());
}

// Extractors
Vector3 Transform::extractPosition(const Matrix& matrix)
{
	float x = matrix.m12, y = matrix.m13, z = matrix.m14;
	return { x, y, z };
}

Matrix Transform::extractRotation(const Matrix& matrix)
{
	Vector3 scale = extractScale(matrix);
	return {
		matrix.m0 / scale.x, matrix.m1 / scale.x, matrix.m2 / scale.x, 0.0f,
		matrix.m4 / scale.y, matrix.m5 / scale.y, matrix.m6 / scale.y, 0.0f,
		matrix.m8 / scale.z, matrix.m9 / scale.z, matrix.m10 / scale.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Vector3 Transform::extractScale(const Matrix& matrix)
{
	float x = Vector3Length({ matrix.m0, matrix.m1, matrix.m2 });
	float y = Vector3Length({ matrix.m4, matrix.m5, matrix.m6 });
	float z = Vector3Length({ matrix.m8, matrix.m9, matrix.m10 });
	return { x, y, z };
}

// Transforms local matrix to parent matrix.
// Applies matrices in the following order:
// Scale -> Rotation -> Translation
Matrix Transform::_makeLocalToParentMatrix() const
{
	// Get local matrices
	auto scaleMatrix = MatrixScale(m_scale.x, m_scale.y, m_scale.z);
	auto rotationMatrix = sauna_math::QuaternionToMatrix(QuaternionNormalize(m_rotation));
	auto translationMatrix = MatrixTranslate(m_position.x, m_position.y, m_position.z);

	// Combine. Scale -> Rotation -> Translation
	return MatrixMultiply(MatrixMultiply(scaleMatrix, rotationMatrix), translationMatrix);
}

Matrix Transform::_makeParentToLocalMatrix() const
{
	return MatrixInvert(_makeLocalToParentMatrix());
}

std::string Transform::toString() const
{
	std::string result = "Transform: ";
	result += "Position: (" + std::to_string(m_position.x) + ", " + std::to_string(m_position.y) + ", " + std::to_string(m_position.z) + ")";
	result += " Scale: (" + std::to_string(m_scale.x) + ", " + std::to_string(m_scale.y) + ", " + std::to_string(m_scale.z) + ")";
	result += " Rotation: (" + std::to_string(m_rotation.x) + ", " + std::to_string(m_rotation.y) + ", " + std::to_string(m_rotation.z) + ", " + std::to_string(m_rotation.w) + ")";
	return result;
}

}; // namespace sauna_components
