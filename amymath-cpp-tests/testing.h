#pragma once
#include <stdexcept>
#include <format>
#include <iostream>

#define FailTest(...) throw std::runtime_error(std::format("{} failed at line {}: {}", __FUNCTION__, __LINE__, std::format(__VA_ARGS__)))
#define Assert(cond, ...) if (!(cond)) FailTest("failed assertion {}: {}", #cond, std::format(__VA_ARGS__))

using Test_t = void(*)();

void _RunTests(const char* categoryName, Test_t tests[], size_t numTests);

#define RunTests(category) _RunTests(#category, category, sizeof(category) / sizeof(Test_t))
