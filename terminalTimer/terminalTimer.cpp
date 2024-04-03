#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <conio.h>

class ClockFace {
private:
    std::vector<std::vector<std::string>> clocks_;
    static const std::unordered_map<char, std::vector<std::string>> cache_;
public:

    explicit ClockFace(size_t sz = 2) : clocks_(sz) {
        for (size_t i = 0; i < sz; ++i) {
            clocks_[i] = cache_.at('0');
        }
    }

    void setClocks(time_t seconds) {
        clocks_.clear();

        time_t minutes = seconds / 60;
        time_t hours = minutes / 60;
        seconds %= 60;
        minutes %= 60;

        size_t sz = 6 + ((std::to_string(hours).size() + 1) / 2) * 2;
        clocks_.resize(sz);
        // seconds
        for (size_t i = sz; i > sz - 2; --i) {
            clocks_[i - 1] = cache_.at((seconds % 10) + '0');
            seconds /= 10;
        }
        clocks_[sz - 3] = cache_.at(':');
        // minutes
        for (size_t i = sz - 3; i > sz - 5; --i) {
            clocks_[i - 1] = cache_.at((minutes % 10) + '0');
            minutes /= 10;
        }
        clocks_[sz - 6] = cache_.at(':');
        // hours
        for (size_t i = sz - 6; i > 0; --i) {
            clocks_[i - 1] = cache_.at((hours % 10) + '0');
            hours /= 10;
        }
    }

    void print() {
        if (clocks_.empty())
            throw std::out_of_range("Clocks is empty");
        size_t n = clocks_[0].size();
        for (size_t j = 0; j < n; ++j) {
            for (size_t i = 0; i < clocks_.size(); ++i) {
                std::cout << clocks_[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }
};

const std::unordered_map<char, std::vector<std::string>> ClockFace::cache_ = {
    {'0', {{"******"},
          {"*    *"},
          {"*    *"},
          {"*    *"},
          {"*    *"},
          {"*    *"},
          {"******"}}
    },
    {'1', {{"     *"},
          {"     *"},
          {"     *"},
          {"     *"},
          {"     *"},
          {"     *"},
          {"     *"}}
    },
    {'2', {{"******"},
          {"     *"},
          {"     *"},
          {"******"},
          {"*     "},
          {"*     "},
          {"******"}}
    },
    {'3', {{"******"},
          {"     *"},
          {"     *"},
          {"******"},
          {"     *"},
          {"     *"},
          {"******"}}
    },
    {'4', {{"*    *"},
          {"*    *"},
          {"*    *"},
          {"******"},
          {"     *"},
          {"     *"},
          {"     *"}}
    },
    {'5', {{"******"},
          {"*     "},
          {"*     "},
          {"******"},
          {"     *"},
          {"     *"},
          {"******"}}
    },
    {'6', {{"******"},
          {"*     "},
          {"*     "},
          {"******"},
          {"*    *"},
          {"*    *"},
          {"******"}}
    },
    {'7', {{"******"},
          {"     *"},
          {"     *"},
          {"     *"},
          {"     *"},
          {"     *"},
          {"     *"}}
    },
    {'8', {{"******"},
          {"*    *"},
          {"*    *"},
          {"******"},
          {"*    *"},
          {"*    *"},
          {"******"}}
    },
    {'9', {{"******"},
          {"*    *"},
          {"*    *"},
          {"******"},
          {"     *"},
          {"     *"},
          {"******"}}
    },
    {':', {{"      "},
          {" **** "},
          {" **** "},
          {"      "},
          {" **** "},
          {" **** "},
          {"      "}}
    }
};

class Timer {
private:
    time_t beginTimer_;
    time_t countTimer_;
    ClockFace clock_;
public:
    Timer() : beginTimer_(time(nullptr)), countTimer_(beginTimer_) {}

    void start() {
        beginTimer_ = time(nullptr);
        countTimer_ = time(nullptr);

        std::thread printThread(&Timer::print, this);
        printThread.join();
    }

private:

    void print() {
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
};

int main()
{
    Timer timer;
    timer.start();
    return 0;
}

