#pragma once
#include "amymath-cpp.hpp"

namespace amymath
{
    template<std::floating_point T = float>
    struct Vector2
    {
        constexpr Vector2() :
            x((T)0.0),
            y((T)0.0)
        {}
        
        template<std::floating_point U = T>
        constexpr Vector2(const Vector2<U>& from) :
            x(static_cast<T>(from.x)),
            y(static_cast<T>(from.y))
        {}

        template<std::integral U>
        constexpr Vector2(const Vector2i<U>& from) :
            x(static_cast<T>(from.x)),
            y(static_cast<T>(from.y))
        {}

        template<numeric X = T, numeric Y = T>
        constexpr Vector2(const X& x, const Y& y) :
            x(static_cast<T>(x)),
            y(static_cast<T>(y))
        {}

        T x = (T)0.0;
        T y = (T)0.0;
        
        template<std::floating_point<T> U>
        constexpr Vector2 operator+(const Vector2<U>& other) const
        {
            Vector2 result = { x + other.x, y + other.y };

            return result;
        }

        template<std::floating_point<T> U>
        constexpr Vector2 operator-(const Vector2<U>& other) const
        {
            Vector2 result = { x - other.x, y - other.y };

            return result;
        }

        template<std::floating_point<T> U>
        constexpr Vector2 operator*(const Vector2<U>& other) const
        {
            Vector2 result = { x * other.x, y * other.y };

            return result;
        }

        template<std::floating_point<T> U>
        constexpr Vector2 operator/(const Vector2<U>& other) const
        {
            Vector2 result = { x / other.x, y / other.y };

            return result;
        }

        template<std::floating_point<T> U>
        constexpr Vector2& operator+=(const Vector2<U>& other)
        {
            return *this = { x + other.x, y + other.y };
        }

        template<std::floating_point<T> U>
        constexpr Vector2& operator-=(const Vector2<U>& other)
        {
            return *this = { x - other.x, y - other.y };
        }

        template<std::floating_point<T> U>
        constexpr Vector2& operator*=(const Vector2<U>& other)
        {
            return *this = { x * other.x, y * other.y };
        }

        template<std::floating_point<T> U>
        constexpr Vector2& operator/=(const Vector2<U>& other)
        {
            return *this = { x / other.x, y / other.y };
        }

        template<std::convertible_to<T> U>
        constexpr Vector2 operator+(const U& value) const
        {
            Vector2 result = { x + value, y + value };

            return result;
        }
        
        template<std::convertible_to<T> U>
        constexpr Vector2 operator-(const U& value) const
        {
            Vector2 result = { x - value, y - value };

            return result;
        }
        
        template<std::convertible_to<T> U>
        constexpr Vector2 operator*(const U& value) const
        {
            Vector2 result = { x * value, y * value };

            return result;
        }
        
        template<std::convertible_to<T> U>
        constexpr Vector2 operator/(const U& value) const
        {
            Vector2 result = { x / value, y / value };

            return result;
        }
        
        template<std::convertible_to<T> U>
        constexpr Vector2& operator+=(const U& value)
        {
            return *this = { x + value, y + value };
        }
        
        template<std::convertible_to<T> U>
        constexpr Vector2& operator-=(const U& value)
        {
            return *this = { x - value, y - value };
        }
        
        template<std::convertible_to<T> U>
        constexpr Vector2& operator*=(const U& value)
        {
            return *this = { x * value, y * value };
        }
        
        template<std::convertible_to<T> U>
        constexpr Vector2& operator/=(const U& value)
        {
            return *this = { x / value, y / value };
        }

        constexpr Vector2 Abs() const
        {
            Vector2 result = { std::abs(x), std::abs(y) };

            return result;
        }

        float Angle() const
        {
            float result = std::atan2(y, x);

            return result;
        }

        float AngleTo(const Vector2& to) const
        {
            // todo
        }

        float AngleToPoint(const Vector2& to) const
        {
            return (to - *this).Angle();
        }
    };
}
