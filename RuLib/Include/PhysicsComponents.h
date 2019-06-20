#pragma once
#include "ECS.h"
#include "Transform.h"

//All Sorts of Physics Components

namespace ru
{

    class CircleComponent : public Component
    {
    public:
        bool awake = false;
        float radius;
        glm::vec2 position;
    };

    class RectangleComponent : public Component
    {
    public:
        bool awake = false;
        ru::Rect rect;
    };

    class LineComponent : public Component
    {
    public:
        glm::vec2 a;
        glm::vec2 b;

        float length;
        glm::vec2 direction;
    };
}
