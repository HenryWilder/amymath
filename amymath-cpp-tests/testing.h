#pragma once
#include <exception>
#include <string>
#include <format>

namespace test_exceptions
{
    class FailedTestException :
    public std::exception
    {
    public:
        FailedTestException(
            const std::string& test,
            size_t line,
            const std::string& msg
        ) :
            std::exception(),
            test(test),
            line(line),
            msg(msg)
        {
            buffer = Message();
        }

        virtual std::string Message() const
        {
            return std::format("{} failed at line {}: \"{}\"", test, line, msg);
        }

        const char *what() const noexcept override
        {
            return buffer.c_str();
        }

    private:
        std::string test;
        size_t line;
        std::string msg;

    protected:
        std::string buffer;
    };

    class FailedAssertionException :
        public FailedTestException
    {
    public:
        FailedAssertionException(
            const std::string& test,
            size_t line,
            const std::string& msg,
            const std::string& expr
        ) :
            FailedTestException(test, line, msg)
        {
            buffer = Message();
        }

        std::string Message() const override
        {
            return std::format("{}\n  failed assertion: {}", FailedTestException::Message(), expr);
        }

    private:
        std::string expr;
    };
    
    class FailedComparisonException :
        public FailedAssertionException
    {
    public:
        FailedComparisonException(
            const std::string& test,
            size_t line,
            const std::string& msg,
            const std::string& expr,
            const std::string& lhs,
            const std::string& rhs
        ) :
            FailedAssertionException(test, line, msg, expr),
            lhs(lhs),
            rhs(rhs)
        {
            buffer = Message();
        }
    
        std::string Message() const override
        {
            return std::format("{}\n    lhs: {}\n    rhs: {}", FailedAssertionException::Message(), lhs, rhs);
        }

    private:
        std::string lhs;
        std::string rhs;
    };
}

#define FailTest(msg) { throw test_exceptions::FailedTestException(__func__, __LINE__, msg); }

#define Assert(condition, msg) { if (!(condition)) { throw test_exceptions::FailedAssertionException(__func__, __LINE__, msg, #condition); } }

#define _AssertCmp(cmp, lhs, rhs, msg) { if (!((lhs) cmp (rhs))) { \
    throw test_exceptions::FailedComparisonException(__func__, __LINE__, msg, (#lhs" "#cmp" "#rhs), std::string(lhs), std::string(rhs)); } \
}

#define AssertEq(lhs, rhs, msg) _AssertCmp(==, lhs, rhs, msg)
#define AssertNe(lhs, rhs, msg) _AssertCmp(!=, lhs, rhs, msg)
#define AssertGt(lhs, rhs, msg) _AssertCmp(>,  lhs, rhs, msg)
#define AssertGe(lhs, rhs, msg) _AssertCmp(>=, lhs, rhs, msg)
#define AssertLt(lhs, rhs, msg) _AssertCmp(<,  lhs, rhs, msg)
#define AssertLe(lhs, rhs, msg) _AssertCmp(<=, lhs, rhs, msg)
