#include "Timer.hpp"

#include <iostream>
#include <thread>
#include <conio.h>

Timer::Timer() noexcept : beginTimer_(time(nullptr)), countTimer_(beginTimer_) {}

void Timer::start() {
    beginTimer_ = time(nullptr);
    countTimer_ = time(nullptr);

    std::thread printThread(&Timer::print, this);
    printThread.join();
}

void Timer::print() {
    int num = 0;
    while (_kbhit() == 0 || (num = _getch()) != 32) {
        system("cls");
        countTimer_ = time(nullptr);
        clock_.setClocks(countTimer_ - beginTimer_);
        clock_.print();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << num;
}


