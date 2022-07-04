#include "../Components/Transform.hpp"

struct View
{
    Transform transform;
    float fov = 45.0f;
    bool perspective = true;
    float nearClip = 0.1f;
    float farClip = 100.0f;
};