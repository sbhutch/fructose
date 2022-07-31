#pragma once

#include <chrono>

class timer {
public:
    timer();

    std::chrono::duration<float> elapsed() const;

    std::chrono::duration<float> restart();

private:
    std::chrono::steady_clock::time_point origin;
};
