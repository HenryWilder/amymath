#pragma once
#include <type_traits>
#include <array>

namespace std
{
    template<class T>
    concept arithmetic = std::is_arithmetic_v<T>;
}

namespace amymath
{
    // constexpr power
    template<std::arithmetic T>
    constexpr T cpow(const T base, const size_t exponent)
    {
        T result = 1;
        for (size_t i = 1; i <= exponent; ++i)
        {
            result *= base;
        }
        return result;
    }

    // constexpr abs
    template<std::arithmetic T>
    constexpr T cabs(const T x)
    {
        T result = x < 0 ? -x : x;

        return result;
    }

    // constexpr abs
    template<std::arithmetic T>
    constexpr T cclamp(const T x, const T min, const T max)
    {
        T result = x < min ? min : x > max ? max : x;

        return result;
    }
    
    // (a+b)^n
    // Returns an array of `(coef, aPow, bPow)`
    template<size_t n>
    consteval auto BinomialExpansion()
    {
        std::array<std::tuple<size_t, size_t, size_t>, n + 1> result;
        size_t coef = 1;
        size_t aPow = n;
        size_t bPow = 0;
        result[0] = std::tuple(coef, aPow, bPow);
        for (size_t i = 1; i <= n; ++i)
        {
            coef = coef * aPow-- / ++bPow;
            result[i] = std::tuple(coef, aPow, bPow);
        }
        return result;
    }

    // (a+b)^n
    template<size_t n, std::arithmetic T>
    constexpr T ExpandBinomial(const T a, const T b)
    {
        size_t coef = 1;
        size_t aPow = n;
        size_t bPow = 0;
        T result = 0;
        {
            result += static_cast<T>(coef) * amymath::cpow(a, aPow) * amymath::cpow(b, bPow);
        }
        for (size_t i = 1; i <= n; ++i)
        {
            coef = coef * aPow-- / ++bPow;
            result += static_cast<T>(coef) * amymath::cpow(a, aPow) * amymath::cpow(b, bPow);
        }
        return result;
    }
}
