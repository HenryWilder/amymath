#include "categories.h"
#include <calc.hpp>
using namespace amy::calc;

static void Test1()
{
    std::cout << (-(5_mx + 3_mx * (2_mx ^ 7_mx))).Sqrt().ToString() << '\n';
}

static void Test2()
{

}

Test_t calcTests[] = {
    Test1,
    Test2,
};
