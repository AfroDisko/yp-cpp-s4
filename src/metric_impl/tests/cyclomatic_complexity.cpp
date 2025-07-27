#include "metric_impl/cyclomatic_complexity.hpp"

#include <gtest/gtest.h>

namespace analyser::metric::metric_impl {

TEST(TestMetrics, CyclomaticComplexityComments) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CyclomaticComplexityMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/comments.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 2) << functions.front().ast;
}

TEST(TestMetrics, CyclomaticComplexityExceptions) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CyclomaticComplexityMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/exceptions.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 3) << functions.front().ast;
}

TEST(TestMetrics, CyclomaticComplexityIf) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CyclomaticComplexityMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/if.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 1) << functions.front().ast;
}

TEST(TestMetrics, CyclomaticComplexityLoops) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CyclomaticComplexityMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/loops.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 4) << functions.front().ast;
}

TEST(TestMetrics, CyclomaticComplexityManyLines) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CyclomaticComplexityMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/many_lines.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 2) << functions.front().ast;
}

TEST(TestMetrics, CyclomaticComplexityManyParameters) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CyclomaticComplexityMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/many_parameters.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 2) << functions.front().ast;
}

TEST(TestMetrics, CyclomaticComplexityMatchCase) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CyclomaticComplexityMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/match_case.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 2) << functions.front().ast;
}

TEST(TestMetrics, CyclomaticComplexityNestedIf) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CyclomaticComplexityMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/nested_if.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 2) << functions.front().ast;
}

TEST(TestMetrics, CyclomaticComplexitySimple) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CyclomaticComplexityMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/simple.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 2) << functions.front().ast;
}

TEST(TestMetrics, CyclomaticComplexityTernary) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CyclomaticComplexityMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/ternary.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 3) << functions.front().ast;
}

}  // namespace analyser::metric::metric_impl
