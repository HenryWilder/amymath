#include "Calc.hpp"

namespace amymath::calc
{
    MathExpr MathExpr::Sqrt() const
    {
        return (*this)^(1_mx / 2);
    }

    std::string MathExpr::ToString() const
    {
        switch (tag)
        {
        case Tag::Var: return std::format("{}", var);
        case Tag::Num: return std::format("{}", num);
        case Tag::Neg: return std::format("(-{})", rhs->ToString());
        case Tag::Add: return std::format("({}+{})", lhs->ToString(), rhs->ToString());
        case Tag::Mul:
            return (lhs->tag == Tag::Num && rhs->tag == Tag::Num)
                ? std::format("({}*{})", lhs->ToString(), rhs->ToString())
                : std::format("({}{})",  lhs->ToString(), rhs->ToString());
        case Tag::Div: return std::format("({}/{})", lhs->ToString(), rhs->ToString());
        case Tag::Pow: return std::format("({}^{})", lhs->ToString(), rhs->ToString());
        }
        return "[ERROR]";
    }

    MathExpr operator+(const MathExpr& a, size_t b) { return a + MathExpr(b); }
    MathExpr operator-(const MathExpr& a, size_t b) { return a - MathExpr(b); }
    MathExpr operator*(const MathExpr& a, size_t b) { return a * MathExpr(b); }
    MathExpr operator/(const MathExpr& a, size_t b) { return a / MathExpr(b); }
    MathExpr operator^(const MathExpr& a, size_t b) { return a ^ MathExpr(b); }
    MathExpr operator+(size_t a, const MathExpr& b) { return MathExpr(a) + b; }
    MathExpr operator-(size_t a, const MathExpr& b) { return MathExpr(a) - b; }
    MathExpr operator*(size_t a, const MathExpr& b) { return MathExpr(a) * b; }
    MathExpr operator/(size_t a, const MathExpr& b) { return MathExpr(a) / b; }
    MathExpr operator^(size_t a, const MathExpr& b) { return MathExpr(a) ^ b; }

    // Try to evaluate the formula
    FormulaResult Formula::operator()(const Number& x) const
    {
        // todo
        return std::nullopt;
    }

    Formula::Rewritten Formula::Factor() const
    {
        // todo
        return std::nullopt;
    }

    Formula::Rewritten Formula::Conjugate() const
    {
        // todo
        return std::nullopt;
    }

    Formula::Rewritten Formula::ApplyTrigIdentity() const
    {
        // todo
        return std::nullopt;
    }

    Formula::Rewritten Formula::Rewrite() const
    {
        if (Rewritten g = Factor())
        {
            return g;
        }
        else if (Rewritten g = Conjugate())
        {
            return g;
        }
        else if (Rewritten g = ApplyTrigIdentity())
        {
            return g;
        }
        return std::nullopt;
    }

    // limit of f(x) as x -> a
    // $\lim_{{x}\to{a}}{f{\left({x}\right)}}$
    Solution Limit(const Formula& f, Number a)
    {
        if (FormulaResult y = f(a))
        {
            return y.value();
        }
        else
        {
            if (Formula::Rewritten rewritten = f.Rewrite())
            {
                return Limit(rewritten.value(), a);
            }
            else
            {
                // todo: approximate
                return NotANumber::DoesNotExist;
            }
        }
    }
}
