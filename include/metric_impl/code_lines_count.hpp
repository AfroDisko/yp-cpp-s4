#pragma once
#include <unistd.h>

#include <string>

#include "metric.hpp"

namespace analyser::metric::metric_impl {

struct CodeLinesCountMetric final: IMetric {
protected:
    virtual std::string Name() const override { return "Code lines count"; }
    virtual MetricResult::ValueType CalculateImpl(const function::Function&) const override;
};

} // namespace analyser::metric::metric_impl
