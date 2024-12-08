#pragma once

#include "components/transform.h"

namespace sauna_core
{

// Base scene interface
class Scene
{
public:
	Scene();
	Scene(const Scene& copy) = delete; // disallow copies
	virtual ~Scene() = default;

	virtual void setup() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void cleanup() = 0;
protected:
	sauna_components::Transform m_rootTransform;
};

}; // namespace sauna_core
