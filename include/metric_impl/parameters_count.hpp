#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#include "metric.hpp"

namespace analyser::metric::metric_impl {

struct CountParametersMetric final: public IMetric {
protected:
    virtual std::string Name() const override { return "Parameters count"; }
    virtual MetricResult::ValueType CalculateImpl(const function::Function&) const override;
};

} // namespace analyser::metric::metric_impl
