#include "metric_impl/code_lines_count.hpp"

#include <filesystem>
#include <gtest/gtest.h>

namespace analyser::metric::metric_impl {

TEST(TestMetrics, CodeLinesCountComments) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CodeLinesCountMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/comments.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 4) << functions.front().ast;
}

TEST(TestMetrics, CodeLinesCountExceptions) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CodeLinesCountMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/exceptions.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 8) << functions.front().ast;
}

TEST(TestMetrics, CodeLinesCountIf) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CodeLinesCountMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/if.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 4) << functions.front().ast;
}

TEST(TestMetrics, CodeLinesCountLoops) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CodeLinesCountMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/loops.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 7) << functions.front().ast;
}

TEST(TestMetrics, CodeLinesCountManyLines) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CodeLinesCountMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/many_lines.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 15) << functions.front().ast;
}

TEST(TestMetrics, CodeLinesCountManyParameters) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CodeLinesCountMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/many_parameters.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 2) << functions.front().ast;
}

TEST(TestMetrics, CodeLinesCountMatchCase) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CodeLinesCountMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/match_case.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 8) << functions.front().ast;
}

TEST(TestMetrics, CodeLinesCountNestedIf) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CodeLinesCountMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/nested_if.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 9) << functions.front().ast;
}

TEST(TestMetrics, CodeLinesCountSimple) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CodeLinesCountMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/simple.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 7) << functions.front().ast;
}

TEST(TestMetrics, CodeLinesCountTernary) {
    function::FunctionExtractor extractor;
    auto metric = std::make_unique<metric_impl::CodeLinesCountMetric>();

    auto functions = extractor.Get(file::File("/workspaces/yp-cpp-s4/src/metric_impl/tests/files/ternary.py"));
    auto result = metric->Calculate(functions.front());
    ASSERT_EQ(std::get<std::size_t>(result.value), 2) << functions.front().ast;
}

}  // namespace analyser::metric::metric_impl
