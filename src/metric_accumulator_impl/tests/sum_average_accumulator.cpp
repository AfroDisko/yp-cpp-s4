#include "metric_accumulator_impl/sum_average_accumulator.hpp"

#include <gtest/gtest.h>
#include <stdexcept>

namespace analyser::metric_accumulator::metric_accumulator_impl::test {

TEST(TestAccumulators, SumAverageAccumulatorGet) {
    SumAverageAccumulator accumulator;

    metric::MetricResult result1 = {"name1", std::size_t(1)};
    metric::MetricResult result2 = {"name1", std::size_t(3)};

    accumulator.Accumulate(result1);
    accumulator.Accumulate(result2);
    accumulator.Finalize();

    auto result = accumulator.Get();

    ASSERT_EQ(result.sum, 4);
    ASSERT_DOUBLE_EQ(result.average, 2.);
}

TEST(TestAccumulators, SumAverageAccumulatorGetWOFinalize) {
    SumAverageAccumulator accumulator;

    metric::MetricResult result1 = {"name1", std::size_t(1)};
    metric::MetricResult result2 = {"name1", std::size_t(3)};

    accumulator.Accumulate(result1);
    accumulator.Accumulate(result2);

    ASSERT_THROW(accumulator.Get(), std::runtime_error);
}

TEST(TestAccumulators, SumAverageAccumulatorReset) {
    SumAverageAccumulator accumulator;

    metric::MetricResult result1 = {"name1", std::size_t(1)};
    metric::MetricResult result2 = {"name1", std::size_t(3)};

    accumulator.Accumulate(result1);
    accumulator.Finalize();

    ASSERT_EQ(accumulator.Get().sum, 1);
    ASSERT_DOUBLE_EQ(accumulator.Get().average, 1.);

    accumulator.Reset();
    accumulator.Accumulate(result2);
    accumulator.Finalize();

    ASSERT_EQ(accumulator.Get().sum, 3);
    ASSERT_DOUBLE_EQ(accumulator.Get().average, 3.);
}

TEST(TestAccumulators, SumAverageAccumulatorAccumulateWrongType) {
    SumAverageAccumulator accumulator;

    metric::MetricResult result1 = {"name1", std::string{}};

    ASSERT_THROW(accumulator.Accumulate(result1), std::runtime_error);
}

TEST(TestAccumulators, SumAverageAccumulatorDangerousFinalize) {
    SumAverageAccumulator accumulator;

    accumulator.Finalize();

    ASSERT_EQ(accumulator.Get().sum, 0);
    ASSERT_EQ(accumulator.Get().average, 0.);
}

}  // namespace analyser::metric_accumulator::metric_accumulator_impl::test
