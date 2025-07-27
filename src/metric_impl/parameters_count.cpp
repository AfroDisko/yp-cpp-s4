#include "metric_impl/parameters_count.hpp"
#include <stdexcept>

namespace analyser::metric::metric_impl {

MetricResult::ValueType CountParametersMetric::CalculateImpl(const function::Function& function) const {
    static constexpr std::string_view delimiter = "\n";

    static auto is_parameters = [](auto&& subrange) {
        return std::string_view(subrange).find("parameters") != std::string::npos; 
    };

    static auto is_body = [](auto&& subrange) {
        return std::string_view(subrange).find("body") != std::string::npos;
    };

    static auto is_identifier = [](auto&& subrange) {
        return std::string_view(subrange).find("identifier") != std::string::npos;
    };

    auto line_by_line = function.ast | std::views::split(delimiter);
    auto it_parameters = std::ranges::find_if(line_by_line, is_parameters);
    if(it_parameters == line_by_line.end()) {
        throw std::runtime_error("cannot find parameters block in function ast");
    }

    auto it_body = std::ranges::find_if(line_by_line, is_body);
    if(it_body == line_by_line.end()) {
        throw std::runtime_error("cannot find body block in function ast");
    }

    return static_cast<std::size_t>(std::ranges::count_if(std::ranges::subrange(it_parameters, it_body), is_identifier));
}

}  // namespace analyser::metric::metric_impl
