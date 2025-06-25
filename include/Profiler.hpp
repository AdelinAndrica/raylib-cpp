#pragma once
#include <chrono>
#include <string>
#include "Logger.hpp"

class ProfilerScope
{
public:
    ProfilerScope(const std::string &name)
        : name(name), start(std::chrono::high_resolution_clock::now()) {}

    ~ProfilerScope()
    {
        auto end = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        LOG_DEBUG("[PROFILE] " + name + " took " + std::to_string(ms) + " us");
    }

private:
    std::string name;
    std::chrono::high_resolution_clock::time_point start;
};

#define PROFILE_SCOPE(name) ProfilerScope profilerScope##__LINE__(name)