#include <iostream>
#include <amymath-cpp.hpp>
#include "testing.h"

using namespace amymath;

void Test1()
{
    Vector2 x(2.0, 3.0);
    Vector2 y(3.0, 3.0);
    AssertLt(x, y, "test");
}

void Test2()
{
    Vector2 x(2.0, 3.0);
    Vector2 y(3.0, 3.0);
    Vector2 z(5.0, 6.0);
    AssertEq(x + y, z, "test");
}

static_assert(Vector2(2.0, 3.0) + Vector2(3.0, 3.0) == Vector2(5.0, 6.0), "constexpr equality");
static_assert(Vector2(-2.0, 3.0).Abs() == Vector2(2.0, 3.0), "constexpr abs");
static_assert((Vector2(-2.0, 3.0) += 6) == Vector2(4.0, 9.0), "constexpr add assign value");

int main()
{
    using Test_t = void(*)();

    Test_t tests[] = {
        Test1,
        Test2,
    };

    int numTestsRun = 0;
    int numTestsPassed = 0;
    for (Test_t test : tests)
    {
        try
        {
            test();
            ++numTestsPassed;
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << "\n\n";
        }
        ++numTestsRun;
    }

    std::cout
        << "passed: " << numTestsPassed << '\n'
        << "failed: " << (numTestsRun - numTestsPassed) << '\n';
}
