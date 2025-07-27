#include <unistd.h>

#include <string>
#include <vector>

#include "file.hpp"
#include "function.hpp"
#include "metric.hpp"
#include "metric_accumulator.hpp"

namespace analyser {

using AnalysisEntry = std::pair<function::Function, metric::MetricResults>;
using Analysis = std::vector<AnalysisEntry>;
using AnalysisByClass = std::vector<Analysis>;
using AnalysisByFiles = std::vector<Analysis>;

Analysis AnalyseFunctions(const std::vector<std::string>& files,
                      const analyser::metric::MetricExtractor& metric_extractor) {
    static constexpr auto extract_functions = [](const std::string& path) {
        return function::FunctionExtractor().Get(file::File(path));
    };

    auto extract_metrics = [&metric_extractor](const function::Function& function) {
        return std::pair{function, metric_extractor.Get(function)};
    };

    return std::ranges::to<Analysis>(files | std::views::transform(extract_functions) | std::views::join | std::views::transform(extract_metrics));
}

AnalysisByClass SplitByClasses(const Analysis& analysis) {
    static constexpr auto has_class = [](const AnalysisEntry& entry) {
        return entry.first.class_name.has_value();
    };

    static constexpr auto sort_comparator = [](const AnalysisEntry& lhs, const AnalysisEntry& rhs) {
        return lhs.first.class_name.value() < rhs.first.class_name.value();
    };

    static constexpr auto chunk_comparator = [](const AnalysisEntry& lhs, const AnalysisEntry& rhs) {
        return lhs.first.class_name.value() == rhs.first.class_name.value();
    };

    Analysis copy(std::ranges::to<Analysis>(analysis | std::views::filter(has_class)));
    std::ranges::sort(copy, sort_comparator);

    return std::ranges::to<AnalysisByClass>(copy | std::views::chunk_by(chunk_comparator));
}

AnalysisByFiles SplitByFiles(const Analysis& analysis) {
    static constexpr auto sort_comparator = [](const AnalysisEntry& lhs, const AnalysisEntry& rhs) {
        return lhs.first.name < rhs.first.name;
    };

    static constexpr auto chunk_comparator = [](const AnalysisEntry& lhs, const AnalysisEntry& rhs) {
        return lhs.first.name == rhs.first.name;
    };

    Analysis copy(analysis);
    std::ranges::sort(copy, sort_comparator);

    return std::ranges::to<AnalysisByFiles>(copy | std::views::chunk_by(chunk_comparator));
}

void AccumulateFunctionAnalysis(const Analysis& analysis, const metric_accumulator::MetricsAccumulator& accumulator) {
    auto accumulate = [&accumulator](const AnalysisEntry& entry) {
        accumulator.AccumulateNextFunctionResults(entry.second);
    };
    std::ranges::for_each(analysis, accumulate);
}

} // namespace analyser
