#include "Timer.hpp"

#include <iostream>
#include <thread>
#include <conio.h>

Timer::Timer() noexcept : beginTimer_(time(nullptr)), countTimer_(beginTimer_), isPause(true) {}

void Timer::start() {
    beginTimer_ = time(nullptr);
    countTimer_ = time(nullptr);

    std::thread printThread(&Timer::print, this);
    printThread.join();
    return start();
}

void Timer::print() {
    int num = 0;
    time_t prevTime = 0;
    while (_kbhit() == 0 || (num = _getch()) != 13) { // Enter
        system("cls");
        if (num == 32) { // space
            if (!isPause) {
                prevTime = countTimer_ - beginTimer_;
            }
            else {
                beginTimer_ = time(nullptr) - prevTime;
            }
            isPause = !isPause;
            num = 0;
        }
        if (!isPause) {
            countTimer_ = time(nullptr);
        }
        clock_.setClocks(countTimer_ - beginTimer_);
        clock_.print();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << num;
}


