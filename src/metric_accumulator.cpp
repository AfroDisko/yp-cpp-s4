#include "metric_accumulator.hpp"

#include <unistd.h>

namespace analyser::metric_accumulator {

void MetricsAccumulator::AccumulateNextFunctionResults(const std::vector<metric::MetricResult> &metric_results) const {
    auto accumulate = [this](const metric::MetricResult& result) {
        auto it = accumulators.find(result.metric_name);
        if(it == accumulators.end()) {
            throw std::runtime_error(std::format("accumulator for metric {} is not registered", result.metric_name));
        }
        it->second->Accumulate(result);
    };

    std::ranges::for_each(metric_results, [&accumulate](const metric::MetricResult& result){ accumulate(result); });
}

void MetricsAccumulator::ResetAccumulators() {
    std::ranges::for_each(accumulators | std::views::values, [](std::shared_ptr<IAccumulator>& acc){ acc->Reset(); });
}

}  // namespace analyser::metric_accumulator
