#pragma once
#include <concepts>

namespace amymath
{
    // Handle name collision
#ifdef RL_VECTOR2_TYPE
    using rlVector2 = ::Vector2;
#endif

    template<std::floating_point T = float>
    struct Vector2;
    
    template<std::integral T = int>
    struct Vector2i;
    
    template<std::floating_point T = float>
    struct Vector3;
    
    template<std::integral T = int>
    struct Vector3i;

    template<std::floating_point T = float>
    struct Vector4;

    template<std::floating_point T = float>
    using Quaternion = Vector4<T>;

    template<std::integral T = int>
    struct Vector4i;

    template<std::floating_point T = float>
    struct Rect2;

    template<std::integral T = int>
    struct Rect2i;

    template<std::floating_point T = float>
    struct Transform2D;

    template<std::floating_point T = float>
    struct Transform3D;
}
