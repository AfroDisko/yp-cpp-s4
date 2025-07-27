#pragma once

#include <memory>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

#include "metric.hpp"

namespace analyser::metric_accumulator {

struct IAccumulator {
    virtual ~IAccumulator() = default;

    virtual void Accumulate(const metric::MetricResult&) = 0;
    virtual void Finalize() = 0;
    virtual void Reset() = 0;

    bool IsFinalized() const { return is_finalized; }

protected:
    bool is_finalized = false;
};

struct MetricsAccumulator {
    template <typename Accumulator>
    void RegisterAccumulator(const std::string& metric_name, std::unique_ptr<Accumulator> acc) {
        accumulators[metric_name] = std::move(acc);
    }

    template <typename Accumulator>
    const Accumulator& GetFinalizedAccumulator(const std::string& metric_name) const {
        auto it = accumulators.find(metric_name);
        if(it == accumulators.end()) {
            throw std::runtime_error(std::format("accumulator for metric {} does not exist", metric_name));
        }
        if(!it->second->IsFinalized()) {
            it->second->Finalize();
        }
        const Accumulator* ptr = dynamic_cast<const Accumulator*>(it->second.get());
        if(!ptr) {
            throw std::runtime_error("bad cast");
        }
        return *ptr;
    }

    void AccumulateNextFunctionResults(
        const std::vector<metric::MetricResult>& metric_results) const;

    void ResetAccumulators();

private:
    std::unordered_map<std::string, std::shared_ptr<IAccumulator>> accumulators;
};

} // namespace analyser::metric_accumulator
