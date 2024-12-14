#include "./test_actor.h"
#include "../components/box_render_component.h"

namespace sauna_game
{

TestActor::TestActor(Scene* scene) : Actor(scene)
{
    this->addComponent<BoxRenderComponent>(&this->transform, Vector3One(), RED);
}

}; // namespace sauna_game