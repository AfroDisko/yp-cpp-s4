#include "metric.hpp"

#include <unistd.h>

#include "function.hpp"

namespace analyser::metric {

void MetricExtractor::RegisterMetric(std::unique_ptr<IMetric> metric) {
    metrics.push_back(std::move(metric));
}

MetricResults MetricExtractor::Get(const function::Function &func) const {
    auto calculate = [&func](const std::unique_ptr<IMetric>& metric) {
        return metric->Calculate(func);
    };

    return std::ranges::to<MetricResults>(metrics | std::views::transform(calculate));
}

}  // namespace analyser::metric
