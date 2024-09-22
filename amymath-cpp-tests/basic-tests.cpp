#include "categories.h"

constexpr auto test1 = amy::BinomialExpansion<5>();
static_assert(amy::BinomialExpansion<5>() == std::array<std::tuple<size_t, size_t, size_t>, 6>({
    {  1, 5, 0, },
    {  5, 4, 1, },
    { 10, 3, 2, },
    { 10, 2, 3, },
    {  5, 1, 4, },
    {  1, 0, 5, },
}));

constexpr auto test2 = amy::BinomialExpansion<6>();
static_assert(amy::BinomialExpansion<6>() == std::array<std::tuple<size_t, size_t, size_t>, 7>({
    {  1, 6, 0, },
    {  6, 5, 1, },
    { 15, 4, 2, },
    { 20, 3, 3, },
    { 15, 2, 4, },
    {  6, 1, 5, },
    {  1, 0, 6, },
}));

constexpr auto testx = amy::ExpandBinomial<2>(3, 4);
constexpr auto testy = 3*3 + 2*3*4 + 4*4;
static_assert(amy::ExpandBinomial<2>(3, 4) == (3*3 + 2*3*4 + 4*4));

static void Test1()
{
    amy::Vector2 x(2.0, 3.0);
    amy::Vector2 y(3.0, 3.0);
    Assert(x < y, "test");
}

static void Test2()
{
    amy::Vector2 x(2.0, 3.0);
    amy::Vector2 y(3.0, 3.0);
    amy::Vector2 z(5.0, 6.0);
    Assert(x + y == z, "test");
}

static_assert(amy::Vector2(2.0, 3.0) + amy::Vector2(3.0, 3.0) == amy::Vector2(5.0, 6.0), "constexpr equality");
static_assert(amy::Vector2(-2.0, 3.0).Abs() == amy::Vector2(2.0, 3.0), "constexpr abs");
static_assert((amy::Vector2(-2.0, 3.0) += 6) == amy::Vector2(4.0, 9.0), "constexpr add assign value");

Test_t basicTests[] = {
    Test1,
    Test2,
};
