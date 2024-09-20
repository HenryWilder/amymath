#pragma once
#include <cmath>
#include "const_math.hpp"
#include "types.hpp"

#define todo() static_assert(false, "todo")

namespace amymath
{
    template<std::floating_point T> constexpr Vector2<T> operator+(const T& value, const Vector2<T>& v);
    template<std::floating_point T> constexpr Vector2<T> operator-(const T& value, const Vector2<T>& v);
    template<std::floating_point T> constexpr Vector2<T> operator*(const T& value, const Vector2<T>& v);
    template<std::floating_point T> constexpr Vector2<T> operator/(const T& value, const Vector2<T>& v);

    template<std::floating_point T>
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

    #ifdef RL_VECTOR2_TYPE
        constexpr Vector2(const amymath::rlVector2& from) :
            x(static_cast<T>(from.x)),
            y(static_cast<T>(from.y))
        {}
    #endif

        template<std::integral U>
        constexpr Vector2(const Vector2i<U>& from) :
            x(static_cast<T>(from.x)),
            y(static_cast<T>(from.y))
        {}

        template<std::arithmetic X = T, std::arithmetic Y = T>
        constexpr Vector2(const X& x, const Y& y) :
            x(static_cast<T>(x)),
            y(static_cast<T>(y))
        {}

        T x = (T)0.0;
        T y = (T)0.0;

    #ifdef RL_VECTOR2_TYPE
        constexpr operator rlVector2() const
        {
            return rlVector2{
                static_cast<float>(x),
                static_cast<float>(y),
            };
        }
    #endif

        constexpr Vector2 operator+(const Vector2& other) const
        {
            Vector2 result = { x + other.x, y + other.y };

            return result;
        }

        constexpr Vector2 operator-(const Vector2& other) const
        {
            Vector2 result = { x - other.x, y - other.y };

            return result;
        }

        constexpr Vector2 operator*(const Vector2& other) const
        {
            Vector2 result = { x * other.x, y * other.y };

            return result;
        }

        constexpr Vector2 operator/(const Vector2& other) const
        {
            Vector2 result = { x / other.x, y / other.y };

            return result;
        }

        constexpr Vector2& operator+=(const Vector2& other)
        {
            return *this = { x + other.x, y + other.y };
        }

        constexpr Vector2& operator-=(const Vector2& other)
        {
            return *this = { x - other.x, y - other.y };
        }

        constexpr Vector2& operator*=(const Vector2& other)
        {
            return *this = { x * other.x, y * other.y };
        }

        constexpr Vector2& operator/=(const Vector2& other)
        {
            return *this = { x / other.x, y / other.y };
        }

        constexpr Vector2 operator+(const T& value) const
        {
            Vector2 result = { x + value, y + value };

            return result;
        }

        constexpr Vector2 operator-(const T& value) const
        {
            Vector2 result = { x - value, y - value };

            return result;
        }

        constexpr Vector2 operator*(const T& value) const
        {
            Vector2 result = { x * value, y * value };

            return result;
        }

        constexpr Vector2 operator/(const T& value) const
        {
            Vector2 result = { x / value, y / value };

            return result;
        }

        constexpr Vector2& operator+=(const T& value)
        {
            return *this = { x + value, y + value };
        }

        constexpr Vector2& operator-=(const T& value)
        {
            return *this = { x - value, y - value };
        }

        constexpr Vector2& operator*=(const T& value)
        {
            return *this = { x * value, y * value };
        }

        constexpr Vector2& operator/=(const T& value)
        {
            T reciprocal = (T)1.0 / value;
            return *this = { x * reciprocal, y * reciprocal };
        }

        constexpr auto operator<=>(const Vector2& other) const = default;

        constexpr Vector2 Abs() const
        {
            Vector2 result = {
                amymath::cabs(x),
                amymath::cabs(y),
            };

            return result;
        }

        T Angle() const
        {
            T result = std::atan2(y, x);

            return result;
        }

        T AngleTo(const Vector2& to) const
        {
            T result = Angle() - to.Angle();

            return result;
        }

        T AngleToPoint(const Vector2& to) const
        {
            T result = (to - *this).Angle();

            return result;
        }

        constexpr T Aspect() const
        {
            return x / y;
        }

        static constexpr Vector2 Bezier2ndDerivative(
            const Vector2& p0,
            const Vector2& p1,
            const Vector2& p2,
            const Vector2& p3,
            T t)
        {
            T u = 1 - t;
            return
                (p2 - 2 * p1 + p0) * (6 * u) +
                (p3 - 2 * p2 + p1) * (6 * t);
        }

        static constexpr Vector2 BezierDerivative(
            const Vector2& p0,
            const Vector2& p1,
            const Vector2& p2,
            const Vector2& p3,
            T t)
        {
            T u = 1 - t;
            return
                (p1 - p0) * (3 * u * u) +
                (p2 - p1) * (6 * u * t) +
                (p3 - p2) * (3 * t * t);
        }

        static constexpr Vector2 BezierInterpolate(
            const Vector2& p0,
            const Vector2& p1,
            const Vector2& p2,
            const Vector2& p3,
            T t)
        {
            T u = 1 - t;
            return
                p0 * (u * u * u) +
                p1 * (3 * u * u * t) +
                p2 * (3 * u * t * t) +
                p3 * (t * t * t);
        }

        // reflect
        constexpr Vector2 Bounce(const Vector2& normal) const
        {
            todo();
        }
        
        Vector2 Ceil() const
        {
            Vector2 result = { std::ceil(x), std::ceil(y) };

            return result;
        }
        
        Vector2 Clamp(Vector2 min, Vector2 max) const
        {
            Vector2 result = {
                amymath::cclamp(x, min.x, max.x),
                amymath::cclamp(y, min.y, max.y)
            };

            return result;
        }
        
        Vector2 Clamp(T min, T max) const
        {
            Vector2 result = {
                amymath::cclamp(x, min, max),
                amymath::cclamp(y, min, max)
            };

            return result;
        }
        
        constexpr Vector2 Cross(Vector2 with) const
        {
            todo();
        }
        
        static constexpr Vector2 CubicInterpolate(Vector2 p0, Vector2 p1, Vector2 p2, T t)
        {
            todo();
        }

        constexpr Vector2 DirectionTo(const Vector2& to)
        {
            todo();
        }
    };

    template<std::floating_point T>
    constexpr Vector2<T> operator+(const T& value, const Vector2<T>& v)
    {
        Vector2 result = { value + v.x, value + v.y };

        return result;
    }

    template<std::floating_point T>
    constexpr Vector2<T> operator-(const T& value, const Vector2<T>& v)
    {
        Vector2 result = { value - v.x, value - v.y };

        return result;
    }

    template<std::floating_point T>
    constexpr Vector2<T> operator*(const T& value, const Vector2<T>& v)
    {
        Vector2 result = { value * v.x, value * v.y };

        return result;
    }

    template<std::floating_point T>
    constexpr Vector2<T> operator/(const T& value, const Vector2<T>& v)
    {
        Vector2 result = { value / v.x, value / v.y };

        return result;
    }
}
