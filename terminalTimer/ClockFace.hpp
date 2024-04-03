#pragma once

#include <vector>
#include <string>
#include <unordered_map>

class ClockFace {
private:
    std::vector<std::vector<std::string>> clocks_;
    static const std::unordered_map<char, std::vector<std::string>> cache_;
public:

    explicit ClockFace() noexcept;

    void setClocks(time_t seconds);
    void print() const;
};