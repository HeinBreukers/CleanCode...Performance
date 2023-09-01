#pragma once

#include <algorithm>
#include <limits>

namespace Union
{


struct Sum
{
    float operator()(float in) 
    {
        sum+=in;
        return sum;
    }
    float sum = 0;
};

struct Min
{
    float operator()(float in) 
    {
        min= std::min(min,in);
        return min;
    }
    float min = std::numeric_limits<float>::max();
};

struct Max
{
    float operator()(float in) 
    {
        max= std::max(max,in);
        return max;
    }
    float max = std::numeric_limits<float>::lowest();
};

enum class StatType{
    Sum,
    Min,
    Max
};


struct StatUnion
{
    StatType m_type;
    union
    {
        Sum sum;
        Min min;
        Max max;
    };  

};


}
