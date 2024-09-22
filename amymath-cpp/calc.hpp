#pragma once
#include <optional>
#include <variant>
#include <memory>
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
        enum class Tag {
            Var, Num, Neg, Add, Mul, Div, Pow,
        } tag;
        char var;
        size_t num;
        std::unique_ptr<MathExpr> lhs, rhs;

        MathExpr(Tag tag, const MathExpr& lhs, const MathExpr& rhs) :
            tag(tag),
            var(),
            num(),
            lhs(std::make_unique<MathExpr>(lhs)),
            rhs(std::make_unique<MathExpr>(rhs))
        {}

        MathExpr(Tag tag, std::nullptr_t lhs, const MathExpr& rhs) :
            tag(tag),
            var(),
            num(),
            lhs(),
            rhs(std::make_unique<MathExpr>(rhs))
        {}

        MathExpr(Tag tag, const MathExpr& lhs, std::nullptr_t rhs) :
            tag(tag),
            var(),
            num(),
            lhs(std::make_unique<MathExpr>(lhs)),
            rhs()
        {}

    public:
        constexpr MathExpr(size_t num) :
            tag(Tag::Num),
            num(num),
            var(),
            lhs(),
            rhs()
        {}

        constexpr MathExpr(char var) :
            tag(Tag::Num),
            num(),
            var(var),
            lhs(),
            rhs()
        {}

        MathExpr(const MathExpr& other) :
            tag(other.tag),
            var(other.var),
            num(other.num),
            lhs(other.lhs ? std::make_unique<MathExpr>(*other.lhs) : nullptr),
            rhs(other.rhs ? std::make_unique<MathExpr>(*other.rhs) : nullptr)
        {}

        MathExpr operator-() const { return MathExpr(Tag::Neg, nullptr, *this); }
        MathExpr operator+(const MathExpr& other) const { return MathExpr(Tag::Add, *this,  other); }
        MathExpr operator-(const MathExpr& other) const { return MathExpr(Tag::Add, *this, -other); }
        MathExpr operator*(const MathExpr& other) const { return MathExpr(Tag::Mul, *this,  other); }
        MathExpr operator/(const MathExpr& other) const { return MathExpr(Tag::Div, *this,  other); }
        MathExpr operator^(const MathExpr& other) const { return MathExpr(Tag::Pow, *this,  other); }

        MathExpr Sqrt() const;

        std::string ToString() const;
    };

    inline MathExpr operator""_mx (size_t num)
    {
        return MathExpr(num);
    }

    MathExpr operator+(const MathExpr& a, size_t b);
    MathExpr operator-(const MathExpr& a, size_t b);
    MathExpr operator*(const MathExpr& a, size_t b);
    MathExpr operator/(const MathExpr& a, size_t b);
    MathExpr operator^(const MathExpr& a, size_t b);
    MathExpr operator+(size_t a, const MathExpr& b);
    MathExpr operator-(size_t a, const MathExpr& b);
    MathExpr operator*(size_t a, const MathExpr& b);
    MathExpr operator/(size_t a, const MathExpr& b);
    MathExpr operator^(size_t a, const MathExpr& b);

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
