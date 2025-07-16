#include <cstdlib>
#include <exception>
#include <memory>
#include <stdexcept>
#include <unistd.h>
#include <iostream>

#include "analyse.hpp"
#include "cmd_options.hpp"
#include "file.hpp"
#include "function.hpp"
#include "include/metric.hpp"
#include "include/metric_accumulator.hpp"
#include "include/metric_accumulator_impl/sum_average_accumulator.hpp"
#include "include/metric_impl/code_lines_count.hpp"
#include "metric.hpp"
#include "metric_accumulator.hpp"
#include "metric_accumulator_impl/accumulators.hpp"
#include "metric_impl/metrics.hpp"

void analysis(const std::vector<std::string>& files) {
    using CodeLinesCountMetric = analyser::metric::metric_impl::CodeLinesCountMetric;
    using CyclomaticComplexityMetric = analyser::metric::metric_impl::CyclomaticComplexityMetric;
    using CountParametersMetric = analyser::metric::metric_impl::CountParametersMetric;

    using MetricsAccumulator = analyser::metric_accumulator::MetricsAccumulator;
    using AverageAccumulator = analyser::metric_accumulator::metric_accumulator_impl::AverageAccumulator;

    static const std::string code_lines_str = "Code lines count";
    static const std::string cyclomatic_complexity_str = "Cyclomatic complexity";
    static const std::string count_parameters_str = "Count parameters";

    analyser::metric::MetricExtractor metric_extractor;
    metric_extractor.RegisterMetric(std::make_unique<CodeLinesCountMetric>());
    metric_extractor.RegisterMetric(std::make_unique<CyclomaticComplexityMetric>());
    metric_extractor.RegisterMetric(std::make_unique<CountParametersMetric>());
    const auto analysis = analyser::AnalyseFunctions(files, metric_extractor);

    static auto print_all = [](const analyser::AnalysisEntry& entry) {
        std::cout << std::format("{}[::{}]::{}\n", entry.first.filename, entry.first.class_name.value_or(""), entry.first.name);
    };
    std::ranges::for_each(analysis, print_all);

    MetricsAccumulator accumulator;
    accumulator.RegisterAccumulator(code_lines_str, std::make_unique<AverageAccumulator>());
    accumulator.RegisterAccumulator(cyclomatic_complexity_str, std::make_unique<AverageAccumulator>());
    accumulator.RegisterAccumulator(count_parameters_str, std::make_unique<AverageAccumulator>());

    auto print_by_file = [&accumulator](const analyser::Analysis& analysis) {
        if(analysis.empty()) {
            return;
        }

        analyser::AccumulateFunctionAnalysis(analysis, accumulator);
        std::cout << std::format("Accumulated Analysis for file {}:\n", analysis.front().first.filename);

        auto average_code_lines_count = accumulator.GetFinalizedAccumulator<AverageAccumulator>(code_lines_str);
        std::cout << std::format("\taverage '{}' {}\n", code_lines_str, average_code_lines_count.Get());

        auto average_cyclomatic_complexity = accumulator.GetFinalizedAccumulator<AverageAccumulator>(cyclomatic_complexity_str);
        std::cout << std::format("\taverage '{}' {}", cyclomatic_complexity_str, average_cyclomatic_complexity.Get());

        auto average_parameters_count = accumulator.GetFinalizedAccumulator<AverageAccumulator>(count_parameters_str);
        std::cout << std::format("\taverage '{}' {}", count_parameters_str, average_parameters_count.Get());
    };
    auto by_files = analyser::SplitByClasses(analysis);
    std::ranges::for_each(by_files, print_by_file);
    accumulator.ResetAccumulators();

    auto print_by_class = [&accumulator](const analyser::Analysis& analysis) {
        if(analysis.empty()) {
            return;
        }
        analyser::AccumulateFunctionAnalysis(analysis, accumulator);
        std::cout << std::format("Accumulated Analysis for class {}:\n", analysis.front().first.class_name.value_or(""));

        auto average_code_lines_count = accumulator.GetFinalizedAccumulator<AverageAccumulator>(code_lines_str);
        std::cout << std::format("\taverage '{}' {}\n", code_lines_str, average_code_lines_count.Get());

        auto average_cyclomatic_complexity = accumulator.GetFinalizedAccumulator<AverageAccumulator>(cyclomatic_complexity_str);
        std::cout << std::format("\taverage '{}' {}\n", cyclomatic_complexity_str, average_cyclomatic_complexity.Get());

        auto average_parameters_count = accumulator.GetFinalizedAccumulator<AverageAccumulator>(count_parameters_str);
        std::cout << std::format("\taverage '{}' {}\n", count_parameters_str, average_parameters_count.Get());
    };
    auto by_class = analyser::SplitByClasses(analysis);
    std::ranges::for_each(by_class, print_by_class);
    accumulator.ResetAccumulators();
}

int main(int argc, char *argv[]) {
    try {
        analyser::cmd::ProgramOptions options;
        if(!options.Parse(argc, argv)) {
            throw std::runtime_error("cannot parse options");
        }
        analysis(options.GetFiles());
    } catch (const std::exception& exc) {
        std::cout << std::format("Exception caught: {}", exc.what());
        return EXIT_FAILURE;
    } catch (...) {
        std::cout << "Unexpected exception caught";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
