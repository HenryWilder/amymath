#pragma once
#include "amymath-cpp.hpp"
#include <format>
#include <array>

#if !defined(RL_VECTOR2_TYPE)
extern "C" {
    typedef struct Vector2 {
        float x;
        float y;
    } Vector2;
    #define RL_VECTOR2_TYPE
}
#endif

namespace amymath
{
    using rlVector2 = ::Vector2;

    template<std::floating_point T>
    constexpr amymath::Vector2<T> operator+(const T &value, const amymath::Vector2<T> &v);

    template<std::floating_point T>
    constexpr amymath::Vector2<T> operator-(const T &value, const amymath::Vector2<T>& v);

    template<std::floating_point T>
    constexpr amymath::Vector2<T> operator*(const T &value, const amymath::Vector2<T>& v);

    template<std::floating_point T>
    constexpr amymath::Vector2<T> operator/(const T &value, const amymath::Vector2<T>& v);

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

        constexpr Vector2(const rlVector2 &from) :
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

        constexpr operator rlVector2() const {
            return rlVector2 {
                static_cast<float>(x),
                static_cast<float>(y),
            };
        }

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

    // ```
    //       n   1   n   0   2   -   +    3   -   +    4   -   +   5   -   +   6   -   +
    // (a+b)^5 = 1 a^5 b^0 + 5 a^4 b^1 + 10 a^3 b^2 + 10 a^2 b^3 + 5 a^1 b^4 + 1 a^0 b^5
    //                       5            4            3           2           1    <- a^{} previous
    //           1    *     ---     *    ---     *    ---    *    ---    *    --- 
    //                       1            2            3           4           5    <- b^{} current
    // 
    //       n   1   n   0   2   -   +    3   -   +    4   -   +    5   -   +   6   -   +   7   -   +
    // (a+b)^6 = 1 a^6 b^0 + 6 a^5 b^1 + 15 a^4 b^2 + 20 a^3 b^3 + 15 a^2 b^4 + 6 a^1 b^5 + 1 a^0 b^6
    //                       6            5            4            3           2           1
    //           1     *    ---     *    ---     *    ---    *     ---    *    ---    *    ---
    //                       1            2            3            4           5           6
    // ```
    // multiply power by b's power divide by position
    template<size_t N>
    constexpr auto BinomialExpansion()
    {
        // (coef, aPow, bPow)
        std::array<std::tuple<size_t, size_t, size_t>, N + 1> result;
        size_t coef = 1;
        size_t aPow = N;
        size_t bPow = 0; 
        result[0] = std::tuple(coef, aPow, bPow);
        for (size_t i = 1; i <= N; ++i)
        {
            coef = coef * aPow-- / ++bPow;
            result[i] = std::tuple(coef, aPow, bPow);
        }
        return result;
    }

    constexpr auto test1 = BinomialExpansion<5>();
    static_assert(BinomialExpansion<5>() == std::array<std::tuple<size_t, size_t, size_t>, 6>({
        {  1, 5, 0, },
        {  5, 4, 1, },
        { 10, 3, 2, },
        { 10, 2, 3, },
        {  5, 1, 4, },
        {  1, 0, 5, },
    }));

    constexpr auto test2 = BinomialExpansion<6>();
    static_assert(BinomialExpansion<6>() == std::array<std::tuple<size_t, size_t, size_t>, 7>({
        {  1, 6, 0, },
        {  6, 5, 1, },
        { 15, 4, 2, },
        { 20, 3, 3, },
        { 15, 2, 4, },
        {  6, 1, 5, },
        {  1, 0, 6, },
    }));

    template<amymath::numeric T>
    consteval size_t cpow(const T base, const size_t exponent) {
        T result = 1;
        for (size_t i = 1; i <= exponent; ++i) { result *= base; }
        return result;
    }

    template<size_t N, amymath::numeric T>
    consteval T ExpandBinomial(const T a, const T b)
    {
        size_t coef = 1;
        size_t aPow = N;
        size_t bPow = 0;
        T result = coef * cpow(a, aPow) * cpow(b, bPow);
        for (size_t i = 1; i <= N; ++i)
        {
            coef = coef * aPow-- / ++bPow;
            result += static_cast<T>(coef) * cpow(a, aPow) * cpow(b, bPow);
        }
        return result;
    }

    constexpr auto testx = ExpandBinomial<2>(3, 4);
    constexpr auto testy = 3*3 + 2*3*4 + 4*4;
    static_assert(ExpandBinomial<2>(3, 4) == (3*3 + 2*3*4 + 4*4));

    template<std::floating_point T>
    constexpr amymath::Vector2<T> operator+(const T &value, const amymath::Vector2<T>& v)
    {
        amymath::Vector2 result = { value + v.x, value + v.y };

        return result;
    }
    
    template<std::floating_point T>
    constexpr amymath::Vector2<T> operator-(const T &value, const amymath::Vector2<T>& v)
    {
        amymath::Vector2 result = { value - v.x, value - v.y };

        return result;
    }
    
    template<std::floating_point T>
    constexpr amymath::Vector2<T> operator*(const T &value, const amymath::Vector2<T>& v)
    {
        amymath::Vector2 result = { value * v.x, value * v.y };

        return result;
    }
    
    template<std::floating_point T>
    constexpr amymath::Vector2<T> operator/(const T &value, const amymath::Vector2<T>& v)
    {
        amymath::Vector2 result = { value / v.x, value / v.y };

        return result;
    }
}

// template<std::floating_point T>
// struct std::formatter<amymath::Vector2<T>>
// {
//     constexpr auto parse(std::format_parse_context& ctx)
//     {
//         return ctx.begin();
//     }

//     auto format(const amymath::Vector2<T>& obj, std::format_context& ctx) const
//     {
//         return std::format_to(ctx.out(), "({}, {})", obj.x, obj.y);
//     }
// };
