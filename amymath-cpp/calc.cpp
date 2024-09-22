#include "Calc.hpp"

namespace amymath::calc
{
    std::string MathExpr::ToString() const
    {
        switch (tag)
        {
        case Tag::Var: return std::move(std::string() + var);
        case Tag::Num: return std::move(std::to_string(num));
        case Tag::Neg: return std::move(std::format("(-{})", par[0].ToString()));
        case Tag::Div: return std::move(std::format("({}/{})", par[0].ToString(), par[1].ToString()));
        case Tag::Pow: return std::move(std::format("({}^{})", par[0].ToString(), par[1].ToString()));
        }

        const size_t num_par = par.size();
        size_t total_size = 0;
        std::vector<std::string> parStr;
        parStr.reserve(num_par);
        for (const MathExpr& x : par)
        {
            std::string str = x.ToString();
            total_size += str.size();
            parStr.push_back(std::move(str));
        }
        std::string result;
        result.reserve(2 + total_size + num_par);
        result.push_back('(');
        result += parStr[0];
        for (size_t i = 1; i < num_par; ++i)
        {
            if (tag == Tag::Add)
            {
                result += '+';
            }
            else if (tag == Tag::Mul)
            {
                if (par[i - 1].tag == Tag::Num && par[i].tag == Tag::Num)
                {
                    result += '*';
                }
            }
            result += parStr[i];
        }
        result.push_back(')');
        return std::move(result);
    }

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
