#pragma once

#include <algorithm>
#include <limits>

namespace CLike
{

enum class StatType{
    Sum,
    Min,
    Max
};


struct StatCLike
{
    StatType m_type;
    float data;
};


}
