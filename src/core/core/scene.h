#pragma once

#include "components/transform.h"

namespace sauna_core
{

// Base scene interface
// Scenes are used to isolate a specific part of the games rendering and
// logic. The idea is that each one scene will be active at a time, and
// implement the interface of this class.
//
// NOTE: There is some indirection here, but I feel that is ok considering
// the flexibility it provides. Only one scene should be active at a time,
// so I think the tradeoff is negligible.
//
// TODO: Profile - May want to move to a pure data-oriented setup (json or yaml files)
// TODO: Tried using a pure struct, but couldn't think of a good way to handle it. Rethink.
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
