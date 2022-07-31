#include "timer.hpp"
#include <utility>

timer::timer()
    : origin(std::chrono::steady_clock::now())
{
}

std::chrono::duration<float> timer::elapsed() const
{
    return std::chrono::steady_clock::now() - origin;
}

std::chrono::duration<float> timer::restart()
{
    auto previous = std::exchange(origin, std::chrono::steady_clock::now());
    return origin - previous;
}
