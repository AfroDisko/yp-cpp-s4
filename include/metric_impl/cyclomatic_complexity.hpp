#pragma once
#include <unistd.h>

#include <string>

#include "metric.hpp"

namespace analyser::metric::metric_impl {

struct CyclomaticComplexityMetric: IMetric {
protected:
    virtual std::string Name() const override { return "Cyclomatic complexity"; }
    virtual MetricResult::ValueType CalculateImpl(const function::Function& f) const override;
};

} // namespace analyser::metric::metric_impl
