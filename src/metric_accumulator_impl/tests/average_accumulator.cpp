#include "metric_accumulator_impl/average_accumulator.hpp"

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

namespace analyser::metric_accumulator::metric_accumulator_impl::test {

TEST(TestAccumulators, AverageAccumulatorGet) {
    AverageAccumulator accumulator;

    metric::MetricResult result1 = {"name1", std::size_t(1)};
    metric::MetricResult result2 = {"name1", std::size_t(3)};

    accumulator.Accumulate(result1);
    accumulator.Accumulate(result2);
    accumulator.Finalize();

    ASSERT_EQ(accumulator.Get(), 2);
}

TEST(TestAccumulators, AverageAccumulatorGetWOFinalize) {
    AverageAccumulator accumulator;

    metric::MetricResult result1 = {"name1", std::size_t(1)};
    metric::MetricResult result2 = {"name1", std::size_t(3)};

    accumulator.Accumulate(result1);
    accumulator.Accumulate(result2);

    ASSERT_THROW(accumulator.Get(), std::runtime_error);
}

TEST(TestAccumulators, AverageAccumulatorReset) {
    AverageAccumulator accumulator;

    metric::MetricResult result1 = {"name1", std::size_t(1)};
    metric::MetricResult result2 = {"name1", std::size_t(3)};

    accumulator.Accumulate(result1);
    accumulator.Finalize();

    ASSERT_EQ(accumulator.Get(), 1);

    accumulator.Reset();
    accumulator.Accumulate(result2);
    accumulator.Finalize();

    ASSERT_EQ(accumulator.Get(), 3);
}

TEST(TestAccumulators, AverageAccumulatorAccumulateWrongType) {
    AverageAccumulator accumulator;

    metric::MetricResult result1 = {"name1", std::string{}};

    ASSERT_THROW(accumulator.Accumulate(result1), std::runtime_error);
}

TEST(TestAccumulators, AverageAccumulatorDangerousFinalize) {
    AverageAccumulator accumulator;

    accumulator.Finalize();

    ASSERT_EQ(accumulator.Get(), 0);
}

}  // namespace analyser::metric_accumulator::metric_accumulator_impl::test
