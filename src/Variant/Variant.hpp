#pragma once

#include <variant>
#include <algorithm>
#include <limits>

namespace Variant
{

struct Sum
{
    constexpr float operator()(float in) noexcept
    {
        sum+=in;
        return sum;
    }
    float sum = 0;
};

struct Min
{
    constexpr float operator()(float in) noexcept
    {
        min= std::min(min,in);
        return min;
    }
    float min = std::numeric_limits<float>::max();
};

struct Max
{
    constexpr float operator()(float in) noexcept
    {
        max= std::max(max,in);
        return max;
    }
    float max = std::numeric_limits<float>::lowest();
};


using StatVariant = 
std::variant<
    Sum,
    Min,
    Max
    >;

}
