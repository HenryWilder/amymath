#pragma once
#include <optional>
#include <variant>
#include <vector>
#include <string>
#include <format>

namespace amymath::calc
{
    enum class NotANumber
    {
        PosInfinity  = -1,
        DoesNotExist =  0,
        NegInfinity  = +1,
    };

    using Integer = long long;
    using Real = long double;
    using Number = std::variant<Integer, Real>;

    using Solution = std::variant<Number, NotANumber>;
    
    class MathExpr
    {
    private:
        enum class Tag { Var, Num, Neg, Add, Mul, Div, Pow, } tag;
        char var;
        size_t num;
        std::vector<MathExpr> par;

        constexpr MathExpr(Tag tag, std::initializer_list<MathExpr> par) :
            tag(tag), num(), var(), par(par)
        {}

    public:
        constexpr MathExpr(size_t num) :
            tag(Tag::Num), num(num), var(), par()
        {}

        constexpr MathExpr(char var) :
            tag(Tag::Num), num(), var(var), par()
        {}

        constexpr MathExpr(const MathExpr& other) :
            tag(other.tag),
            var(other.var),
            num(other.num),
            par(other.par)
        {}

        MathExpr operator-() const { return MathExpr(Tag::Neg, { *this }); }
        MathExpr operator+(const MathExpr& other) const { return MathExpr(Tag::Add, { *this,  other }); }
        MathExpr operator-(const MathExpr& other) const { return MathExpr(Tag::Add, { *this, -other }); }
        MathExpr operator*(const MathExpr& other) const { return MathExpr(Tag::Mul, { *this,  other }); }
        MathExpr operator/(const MathExpr& other) const { return MathExpr(Tag::Div, { *this,  other }); }
        MathExpr operator^(const MathExpr& other) const { return MathExpr(Tag::Pow, { *this,  other }); }

        static MathExpr Sum(std::initializer_list<MathExpr> items)
        {
            return MathExpr(Tag::Add, items);
        }

        static MathExpr Prod(std::initializer_list<MathExpr> items)
        {
            return MathExpr(Tag::Mul, items);
        }
        
        MathExpr Sqrt() const;

        std::string ToString() const;
    };

    inline MathExpr operator""_mx (size_t num)
    {
        return MathExpr(num);
    }
        
    inline MathExpr MathExpr::Sqrt() const
    {
        return (*this)^(1_mx / 2_mx);
    }
    
    inline MathExpr operator+(const MathExpr& a, size_t b) { return a + MathExpr(b); }
    inline MathExpr operator-(const MathExpr& a, size_t b) { return a - MathExpr(b); }
    inline MathExpr operator*(const MathExpr& a, size_t b) { return a * MathExpr(b); }
    inline MathExpr operator/(const MathExpr& a, size_t b) { return a / MathExpr(b); }
    inline MathExpr operator^(const MathExpr& a, size_t b) { return a ^ MathExpr(b); }
    inline MathExpr operator+(size_t a, const MathExpr& b) { return MathExpr(a) + b; }
    inline MathExpr operator-(size_t a, const MathExpr& b) { return MathExpr(a) - b; }
    inline MathExpr operator*(size_t a, const MathExpr& b) { return MathExpr(a) * b; }
    inline MathExpr operator/(size_t a, const MathExpr& b) { return MathExpr(a) / b; }
    inline MathExpr operator^(size_t a, const MathExpr& b) { return MathExpr(a) ^ b; }

    using FormulaResult = std::optional<Solution>;

    struct Formula
    {
        // If no value, rewrite was unsuccessful.
        using Rewritten = std::optional<Formula>;

        // Try to evaluate the formula
        FormulaResult operator()(const Number& x) const;

        Rewritten Factor() const;
        Rewritten Conjugate() const;
        Rewritten ApplyTrigIdentity() const;
        Rewritten Rewrite() const;
    };

    // limit of f(x) as x -> a
    // $\lim_{{x}\to{a}}{f{\left({x}\right)}}$
    Solution Limit(const Formula& f, Number a);
};
