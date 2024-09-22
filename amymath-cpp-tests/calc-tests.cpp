#include "categories.h"
#include <calc.hpp>
using namespace amy::calc;

static void Test1()
{
    std::cout << (-(5_mx + 3_mx * (2_mx ^ 7_mx))).Sqrt().ToString() << '\n';
}

static void Test2()
{
    std::cout << (MathExpr::Prod({ 1_mx, 5_mx, 3_mx / 2_mx, 6_mx - 7_mx, 6_mx, 3_mx })).ToString() << '\n';
}

Test_t calcTests[] = {
    Test1,
    Test2,
};
