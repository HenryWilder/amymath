#pragma once
#include <concepts>
#include <cmath>
#include <cstdlib>
#include <limits>

namespace amymath
{
    template<class T>
    concept numeric = std::disjunction_v<std::is_integral<T>, std::is_floating_point<T>>;

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

#include "vector2.hpp"
