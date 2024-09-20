#include "testing.h"

void _RunTests(const char* categoryName, Test_t tests[], size_t numTests)
{
    std::cout << categoryName << '\n';
    int numTestsRun = 0;
    int numTestsPassed = 0;
    for (size_t i = 0; i < numTests; ++i)
    {
        try
        {
            (tests[i])();
            ++numTestsPassed;
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << "\n\n";
        }
        ++numTestsRun;
    }

    std::cout
        << "passed: " << numTestsPassed << '\n'
        << "failed: " << (numTestsRun - numTestsPassed) << "\n\n";
}
