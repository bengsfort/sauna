#pragma once

namespace sauna_scene
{

class Actor
{
public:
    Actor() {}
    virtual ~Actor() = default;

    template<typename ComponentType>
    ComponentType* addComponent();

    template<typename ComponentType>
    ComponentType* getComponent();

    virtual void update(float timeDelta) = 0;
};

}; // namespace sauna_scene