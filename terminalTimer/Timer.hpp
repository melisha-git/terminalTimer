#pragma once

#include "ClockFace.hpp"

class Timer {
private:
    time_t beginTimer_;
    time_t countTimer_;
    ClockFace clock_;
public:
    Timer() noexcept;

    void start();

private:
    void print();
};