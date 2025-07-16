#include "metric_impl/code_lines_count.hpp"

#include <charconv>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <sys/types.h>
#include <unistd.h>

namespace analyser::metric::metric_impl {

MetricResult::ValueType CodeLinesCountMetric::CalculateImpl(const function::Function& function) const {
    static constexpr std::string_view delimiter = "\n";

    static auto is_definition = [](auto&& subrange) -> bool {
        static constexpr std::string_view marker = "function_definition";
        return std::string_view(subrange).find(marker) != std::string::npos;
    };

    static auto is_comment = [](auto&& subrange) -> bool {
        static constexpr std::string_view marker = "comment";
        return std::string_view(subrange).find(marker) != std::string::npos;
    };

    static auto count_lines = [](auto&& subrange) -> std::size_t {
        const std::string_view string(subrange);

        const std::size_t start_bracket = string.find("[");
        const std::size_t start_comma = string.find(",", start_bracket);
        const std::size_t end_bracket = string.find("[", start_comma);
        const std::size_t end_comma = string.find(",", end_bracket);

        std::size_t first_line = 0;
        auto result = std::from_chars(string.data() + start_bracket + 1, string.data() + start_comma, first_line);
        if(result.ec != std::errc()) {
            throw std::runtime_error("failed to parse ast");
        }
        // std::cout << std::format("first line {}\n", first_line);

        std::size_t last_line = 0;
        result = std::from_chars(string.data() + end_bracket + 1, string.data() + end_comma, last_line);
        if(result.ec != std::errc()) {
            throw std::runtime_error("failed to parse ast");
        }
        // std::cout << std::format("last line {}\n", first_line);

        return last_line - first_line + 1;
    };

    auto line_by_line = function.ast | std::views::split(delimiter);

    auto it = std::ranges::find_if(line_by_line, is_definition);
    if(it == line_by_line.end()) {
        throw std::runtime_error("function ast has no definition");
    }
    const std::size_t function_lines = count_lines(*it);
    const std::size_t comment_lines = std::ranges::fold_left(line_by_line | std::views::filter(is_comment) | std::views::transform(count_lines), 0, std::plus<std::size_t>{});

    return function_lines - comment_lines;
}

}  // namespace analyser::metric::metric_impl
