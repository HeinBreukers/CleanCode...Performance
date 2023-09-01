#pragma once

#include <algorithm>
#include <cmath>
#include <limits>

namespace Virtual
{

struct Base
{
    Base()=default;
    virtual ~Base() = default;
    virtual float operator()(float in) = 0;
};

struct Sum: public Base
{
    float operator()(float in) override
    {
        sum+=in;
        return sum;
    }
    float sum = 0;
};

struct Min: public Base
{
    float operator()(float in) override
    {
        min= std::min(min,in);
        return min;
    }
    float min  = std::numeric_limits<float>::max();
};

struct Max: public Base
{
    float operator()(float in) override
    {
        max= std::max(max,in);
        return max;
    }
    float max = std::numeric_limits<float>::lowest();
};



}
