#include <benchmark/benchmark.h>

#include <random>
#include <list>

#include "Virtual.hpp"
#include "Variant.hpp"
#include "Union.hpp"
#include "CLike.hpp"

inline constexpr long start = 100000;
inline constexpr long end = 100000;


std::vector<float> GenData(size_t size)
{
    std::mt19937 rng(1234);
    std::uniform_real_distribution<float> dist;

    std::vector<float> in(size);
    std::generate(std::begin(in),std::end(in), [&]()->float{return dist(rng);});
    return in;
}

std::vector<Virtual::Base*> GenVirtual(size_t size)
{
    std::mt19937 gen(5678); // seed the generator
    std::uniform_int_distribution<> distr(0, 2); // define the range


    std::vector<Virtual::Base*> out;
    std::list<size_t> l;
    for(size_t i = 0; i<size; ++i)
    {
        switch (distr(gen))
        {
        case 0:
            l.push_back(0);
            out.push_back(new Virtual::Max());
            break;
        case 1:
            l.push_back(1);
            out.push_back(new Virtual::Min());
            break;
        case 2:
            l.push_back(2);
            out.push_back(new Virtual::Sum());
            break;
        default:
            break;
        }
    }
    return out;
}

std::vector<Variant::StatVariant> GenVariant(size_t size)
{
    std::mt19937 gen(5678); // seed the generator
    std::uniform_int_distribution<> distr(0, 2); // define the range
    std::vector<Variant::StatVariant> out;
    std::list<size_t> l;
    for(size_t i = 0; i<size; ++i)
    {
        switch (distr(gen))
        {
        case 0:
            l.push_back(0);
            out.push_back(Variant::Max());
            break;
        case 1:
            l.push_back(1);
            out.push_back(Variant::Min());
            break;
        case 2:
            l.push_back(2);
            out.push_back(Variant::Sum());
            break;
        default:
            break;
        }
    }
    return out;
}

std::vector<Union::StatUnion> GenUnion(size_t size)
{
    std::mt19937 gen(5678); // seed the generator
    std::uniform_int_distribution<> distr(0, 2); // define the range
    std::vector<Union::StatUnion> out;
    std::list<size_t> l;
    for(size_t i = 0; i<size; ++i)
    {
        switch (distr(gen))
        {
        case 0:
            l.push_back(0);
            out.push_back({.m_type = Union::StatType::Max, .max = Union::Max()});
            break;
        case 1:
            l.push_back(1);
            out.push_back({.m_type = Union::StatType::Min, .min = Union::Min()});
            break;
        case 2:
            l.push_back(2);
            out.push_back({.m_type = Union::StatType::Sum, .sum = Union::Sum()});
            break;
        default:
            break;
        }
    }
    return out;
}

std::vector<CLike::StatCLike> GenCLike(size_t size)
{
    std::mt19937 gen(5678); // seed the generator
    std::uniform_int_distribution<> distr(0, 2); // define the range
    std::vector<CLike::StatCLike> out;
    std::list<size_t> l;
    for(size_t i = 0; i<size; ++i)
    {
        switch (distr(gen))
        {
        case 0:
            l.push_back(0);
            out.push_back({.m_type = CLike::StatType::Max, .data = std::numeric_limits<float>::lowest()});
            break;
        case 1:
            l.push_back(1);
            out.push_back({.m_type = CLike::StatType::Min, .data = std::numeric_limits<float>::max()});
            break;
        case 2:
            l.push_back(2);
            out.push_back({.m_type = CLike::StatType::Sum, .data = 0});
            break;
        default:
            break;
    }
    }

    return out;
}


static void BM_Virtual(benchmark::State& state) {
  size_t opsNr = static_cast<size_t>(state.range(0));
  auto ops = GenVirtual(opsNr);
  std::vector<float> data = GenData(opsNr);
  for (auto _ : state)
  {
    float out = 0;
    for(size_t i=0; i<opsNr;++i)
    {
        out += ops[i]->operator()(data[i]);
        
    }
    benchmark::DoNotOptimize(out);
  }
}


static void BM_Variant(benchmark::State& state) {
  size_t opsNr = static_cast<size_t>(state.range(0));
  auto ops = GenVariant(opsNr);
  std::vector<float> data = GenData(opsNr);
  for (auto _ : state)
  {
    float out = 0;
    for(size_t i=0; i<opsNr;++i)
    {        
        out += std::visit([rand = data[i]](auto&& arg)
        {
            return arg(rand);
        },ops[i]);
    }
    benchmark::DoNotOptimize(out);
  }
}


static void BM_Union(benchmark::State& state) {
  size_t opsNr = static_cast<size_t>(state.range(0));
  auto ops = GenUnion(opsNr);
  std::vector<float> data = GenData(opsNr);
  for (auto _ : state)
  {
    float out = 0;
    for(size_t i=0; i<opsNr;++i)
    {     
        switch(ops[i].m_type) {
        case Union::StatType::Max :
            out += ops[i].max(data[i]);
            break;
        case Union::StatType::Min:
            out += ops[i].min(data[i]);
            break;
        case Union::StatType::Sum:
            out += ops[i].sum(data[i]);
        break;
        }
    }
    benchmark::DoNotOptimize(out);

  }
}


static void BM_CLike(benchmark::State& state) {
  size_t opsNr = static_cast<size_t>(state.range(0));
  auto ops = GenCLike(opsNr);
  std::vector<float> data = GenData(opsNr);
  for (auto _ : state)
  {
    float out = 0;
    for(size_t i=0; i<opsNr;++i)
    {     
        switch(ops[i].m_type) {
        case CLike::StatType::Sum :
            ops[i].data += data[i];
            break;
        case CLike::StatType::Min:
            ops[i].data = std::min(ops[i].data ,data[i]);
            break;
        case CLike::StatType::Max:
            ops[i].data = std::max(ops[i].data ,data[i]);
            break;
        }
        out += ops[i].data;
    }
    benchmark::DoNotOptimize(out);
  }
}


BENCHMARK(BM_Virtual)->Range(start,end);
BENCHMARK(BM_CLike)->Range(start,end);
BENCHMARK(BM_Union)->Range(start,end);
BENCHMARK(BM_Variant)->Range(start,end);


BENCHMARK_MAIN();