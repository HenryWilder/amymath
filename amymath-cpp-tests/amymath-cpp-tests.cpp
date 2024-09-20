#include <iostream>
#include <amymath-cpp.hpp>
#include "testing.h"

using namespace amymath;

void Test1()
{
    AssertEq("apple", "orange", "string equality");
}

int main()
{
    using Test_t = void(*)();

    Test_t tests[] = {
        Test1,
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
