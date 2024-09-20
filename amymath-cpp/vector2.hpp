#pragma once
#include "amymath-cpp.hpp"
#include <format>

namespace amymath
{
    template<std::floating_point T>
    constexpr Vector2<T> operator+(const T &value, const Vector2<T> &v);

    template<std::floating_point T>
    constexpr Vector2<T> operator-(const T &value, const Vector2<T>& v);

    template<std::floating_point T>
    constexpr Vector2<T> operator*(const T &value, const Vector2<T>& v);

    template<std::floating_point T>
    constexpr Vector2<T> operator/(const T &value, const Vector2<T>& v);


    template<std::floating_point T>
    struct Vector2
    {
        constexpr Vector2() :
            x((T)0.0),
            y((T)0.0)
        {}

        template<std::floating_point U = T>
        constexpr Vector2(const Vector2<U> &from) :
            x(static_cast<T>(from.x)),
            y(static_cast<T>(from.y))
        {}

        template<std::integral U>
        constexpr Vector2(const Vector2i<U> &from) :
            x(static_cast<T>(from.x)),
            y(static_cast<T>(from.y))
        {}

        template<numeric X = T, numeric Y = T>
        constexpr Vector2(const X &x, const Y &y) :
            x(static_cast<T>(x)),
            y(static_cast<T>(y))
        {}

        T x = (T)0.0;
        T y = (T)0.0;

        constexpr Vector2 operator+(const Vector2 &other) const
        {
            Vector2 result = { x + other.x, y + other.y };

            return result;
        }

        constexpr Vector2 operator-(const Vector2 &other) const
        {
            Vector2 result = { x - other.x, y - other.y };

            return result;
        }

        constexpr Vector2 operator*(const Vector2 &other) const
        {
            Vector2 result = { x * other.x, y * other.y };

            return result;
        }

        constexpr Vector2 operator/(const Vector2 &other) const
        {
            Vector2 result = { x / other.x, y / other.y };

            return result;
        }

        constexpr Vector2 &operator+=(const Vector2 &other)
        {
            return *this = { x + other.x, y + other.y };
        }

        constexpr Vector2 &operator-=(const Vector2 &other)
        {
            return *this = { x - other.x, y - other.y };
        }

        constexpr Vector2 &operator*=(const Vector2 &other)
        {
            return *this = { x * other.x, y * other.y };
        }

        constexpr Vector2 &operator/=(const Vector2 &other)
        {
            return *this = { x / other.x, y / other.y };
        }

        constexpr Vector2 operator+(const T &value) const
        {
            Vector2 result = { x + value, y + value };

            return result;
        }
        
        constexpr Vector2 operator-(const T &value) const
        {
            Vector2 result = { x - value, y - value };

            return result;
        }
        
        constexpr Vector2 operator*(const T &value) const
        {
            Vector2 result = { x * value, y * value };

            return result;
        }
        
        constexpr Vector2 operator/(const T &value) const
        {
            Vector2 result = { x / value, y / value };

            return result;
        }
        
        constexpr Vector2 &operator+=(const T &value)
        {
            return *this = { x + value, y + value };
        }
        
        constexpr Vector2 &operator-=(const T &value)
        {
            return *this = { x - value, y - value };
        }
        
        constexpr Vector2 &operator*=(const T &value)
        {
            return *this = { x * value, y * value };
        }

        constexpr Vector2 &operator/=(const T &value)
        {
            T reciprocal = (T)1.0 / value;
            return *this = { x * reciprocal, y * reciprocal };
        }

        constexpr auto operator<=>(const Vector2 &other) const = default;

        constexpr Vector2 Abs() const
        {
            Vector2 result = {
                x < 0 ? -x : x,
                y < 0 ? -y : y,
            };

            return result;
        }

        T Angle() const
        {
            T result = std::atan2(y, x);

            return result;
        }

        T AngleTo(const Vector2 &to) const
        {
            T result = Angle() - to.Angle();

            return result;
        }
        
        T AngleToPoint(const Vector2 &to) const
        {
            T result = (to - *this).Angle();

            return result;
        }

        constexpr T Aspect() const
        {
            return x / y;
        }

        static constexpr Vector2 Bezier2ndDerivative(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, T t)
        {
            T u = 1 - t;
            return
                (6 * u) * (p2 - 2 * p1 + p0) +
                (6 * t) * (p3 - 2 * p2 + p1);
        }

        static constexpr Vector2 BezierDerivative(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, T t)
        {
            T u = 1 - t;
            return
                (3 * u * u) * (p1 - p0) +
                (6 * u * t) * (p2 - p1) +
                (3 * t * t) * (p3 - p2);
        }

        static constexpr Vector2 BezierInterpolate(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, T t)
        {
            T u = 1 - t;
            return
                (    u * u * u) * p0 +
                (3 * u * u * t) * p1 +
                (3 * u * t * t) * p2 +
                (    t * t * t) * p3;
        }

        // reflect
        constexpr Vector2 bounce(const Vector2 &normal) const
        {
            static_assert(false, "todo");
        }
    };

    template<std::floating_point T>
    constexpr Vector2<T> operator+(const T &value, const Vector2<T>& v)
    {
        Vector2 result = { value + v.x, value + v.y };

        return result;
    }
    
    template<std::floating_point T>
    constexpr Vector2<T> operator-(const T &value, const Vector2<T>& v)
    {
        Vector2 result = { value - v.x, value - v.y };

        return result;
    }
    
    template<std::floating_point T>
    constexpr Vector2<T> operator*(const T &value, const Vector2<T>& v)
    {
        Vector2 result = { value * v.x, value * v.y };

        return result;
    }
    
    template<std::floating_point T>
    constexpr Vector2<T> operator/(const T &value, const Vector2<T>& v)
    {
        Vector2 result = { value / v.x, value / v.y };

        return result;
    }
}
    
template<std::floating_point T>
struct std::formatter<amymath::Vector2<T>>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    auto format(const amymath::Vector2<T>& obj, std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "({}, {})", obj.x, obj.y);
    }
};
