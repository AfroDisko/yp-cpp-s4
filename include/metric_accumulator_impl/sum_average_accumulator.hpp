#pragma once
#include <cstddef>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "metric_accumulator.hpp"

namespace analyser::metric_accumulator::metric_accumulator_impl {

struct SumAverageAccumulator: public IAccumulator {
    struct SumAverage {
        std::size_t sum;
        double average;
        auto operator<=>(const SumAverage&) const = default;
    };

    virtual void Accumulate(const metric::MetricResult& metric_result) override;
    virtual void Finalize() override;
    virtual void Reset() override;

    SumAverage Get() const;

private:
    std::size_t sum = 0;
    std::size_t count = 0;
    double average = 0.;
};

} // namespace analyser::metric_accumulator::metric_accumulator_impl
