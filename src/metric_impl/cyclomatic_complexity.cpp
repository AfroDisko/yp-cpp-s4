#include "metric_impl/cyclomatic_complexity.hpp"

#include <unistd.h>

namespace analyser::metric::metric_impl {

MetricResult::ValueType CyclomaticComplexityMetric::CalculateImpl(const function::Function& function) const {
    static constexpr std::string_view delimiter = "\n";

    static constexpr auto is_decision_point = [](auto&& subrange) {
        static constexpr std::array<std::string_view, 7> decision_points = {
            "if_statement",
            "elif_clause",
            "conditional_expression",
            "while_statement",
            "for_statement",
            "except_clause",
            "case_clause"
        };
        
        std::string_view string(subrange);
        auto it = std::ranges::find_if(decision_points, [string](std::string_view statement){ return string.find(statement) != std::string::npos; });
        return it != decision_points.end();
    };

    static constexpr auto is_exit_point = [](auto&& subrange) {
        static constexpr std::array<std::string_view, 1> exit_points = {
            "return_statement"
        };

        std::string_view string(subrange);
        auto it = std::ranges::find_if(exit_points, [string](std::string_view statement){ return string.find(statement) != std::string::npos; });
        return it != exit_points.end();
    };

    auto line_by_line = function.ast | std::views::split(delimiter);
    const std::size_t decision_points_count = std::ranges::count_if(line_by_line, is_decision_point);
    // std::cout << std::format("decision points {}\n", decision_points_count);

    const std::size_t exit_points_count = std::ranges::count_if(line_by_line, is_exit_point);
    // std::cout << std::format("exit points {}\n", exit_points_count);

    return decision_points_count - exit_points_count + 2;
}

}  // namespace analyser::metric::metric_impl
