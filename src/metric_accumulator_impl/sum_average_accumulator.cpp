#include "metric_accumulator_impl/sum_average_accumulator.hpp"

#include <cmath>
#include <stdexcept>
#include <unistd.h>

namespace analyser::metric_accumulator::metric_accumulator_impl {

void SumAverageAccumulator::Accumulate(const metric::MetricResult& metric_result) {
    if(!std::holds_alternative<std::size_t>(metric_result.value)) {
        throw std::runtime_error("incompatiable metric result type");
    }

    sum += std::get<std::size_t>(metric_result.value);
    count += 1;
}

void SumAverageAccumulator::Finalize() {
    average = static_cast<double>(sum) / count;
    if(std::isnan(average)) {
        average = 0;
        std::cout << std::format("SumAverageAccumulator average is NaN. Reset to {}\n", average);
    }
    is_finalized = true;
}

void SumAverageAccumulator::Reset() {
    sum = 0;
    count = 0;
    average = 0.;
    is_finalized = false;
}

SumAverageAccumulator::SumAverage SumAverageAccumulator::Get() const {
    if(!is_finalized) {
        throw std::runtime_error("sum-average accumulator is not finalized");
    }

    return {sum, average};
}

}  // namespace analyser::metric_accumulator::metric_accumulator_impl
