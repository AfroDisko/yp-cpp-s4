#include "metric_impl/parameters_count.hpp"

#include <gtest/gtest.h>

namespace analyser::metric::metric_impl {

TEST(TestMetrics, CountParametersMetricComments) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CountParametersMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/comments.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 3) << functions.front().ast;
}

TEST(TestMetrics, CountParametersMetricExceptions) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CountParametersMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/exceptions.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 0) << functions.front().ast;
}

TEST(TestMetrics, CountParametersMetricIf) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CountParametersMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/if.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 1) << functions.front().ast;
}

TEST(TestMetrics, CountParametersMetricLoops) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CountParametersMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/loops.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 1) << functions.front().ast;
}

TEST(TestMetrics, CountParametersMetricManyLines) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CountParametersMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/many_lines.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 0) << functions.front().ast;
}

TEST(TestMetrics, CountParametersMetricManyParameters) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CountParametersMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/many_parameters.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 5) << functions.front().ast;
}

TEST(TestMetrics, CountParametersMetricMatchCase) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CountParametersMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/match_case.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 1) << functions.front().ast;
}

TEST(TestMetrics, CountParametersMetricNestedIf) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CountParametersMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/nested_if.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 2) << functions.front().ast;
}

TEST(TestMetrics, CountParametersMetricSimple) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CountParametersMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/simple.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 0) << functions.front().ast;
}

TEST(TestMetrics, CountParametersMetricTernary) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CountParametersMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/ternary.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 1) << functions.front().ast;
}

}  // namespace analyser::metric::metric_impl
