#pragma once

#include "metric_accumulator.hpp"

namespace analyser::metric_accumulator::metric_accumulator_impl {

struct AverageAccumulator: public IAccumulator {
    virtual void Accumulate(const metric::MetricResult& metric_result) override;
    virtual void Finalize() override;
    virtual void Reset() override;

    double Get() const;

private:
    std::size_t sum = 0;
    std::size_t count = 0;
    double average = 0.;
};

} // namespace analyser::metric_accumulator::metric_accumulator_impl
