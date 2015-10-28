#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

#include "snyder/metrics_registry.h"

// The fixture for testing class Foo.
class MetricsRegistryCounterTest : public ::testing::Test
{
 protected:
    Snyder::MetricsRegistry* reg;

    MetricsRegistryCounterTest()
    {
    }

    virtual ~MetricsRegistryCounterTest()
    {
    }

    virtual void SetUp()
    {
      reg = new Snyder::MetricsRegistry();
    }

    virtual void TearDown()
    {
      delete reg;
    }

};

// Tests that a simple mustache tag is replaced
TEST_F(MetricsRegistryCounterTest, TestAddSimpleCounter)
{
  reg->Increment("foo");
  auto counters = reg->GetCounters();

  EXPECT_EQ(1, counters["foo"]);
}
TEST_F(MetricsRegistryCounterTest, TestAddCounterWithSpecifiedValue)
{
  reg->Increment("foo", 5);
  auto counters = reg->GetCounters();

  EXPECT_EQ(5, counters["foo"]);
}
TEST_F(MetricsRegistryCounterTest, TestIncrementExistingCounter)
{
  reg->Increment("foo");
  reg->Increment("foo", 5);
  auto counters = reg->GetCounters();

  EXPECT_EQ(6, counters["foo"]);
}
TEST_F(MetricsRegistryCounterTest, TestClearCounters)
{
  reg->Increment("foo");
  auto counters = reg->GetCounters();
  EXPECT_EQ(1, counters["foo"]);
  reg->ResetCounters();
  auto counters2 = reg->GetCounters();
  EXPECT_EQ(0, counters2["foo"]);
}
TEST_F(MetricsRegistryCounterTest, TestDecrementCounters)
{
  reg->Increment("foo", 5);
  reg->Decrement("foo");
  auto counters = reg->GetCounters();
  EXPECT_EQ(4, counters["foo"]);
  reg->Decrement("foo", 2);
  auto counters2 = reg->GetCounters();
  EXPECT_EQ(2, counters2["foo"]);
}
TEST_F(MetricsRegistryCounterTest, TestDecrementCountersBeyondZero)
{
  reg->Increment("foo", 5);
  int res = reg->Decrement("foo", 6);
  auto counters = reg->GetCounters();
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, counters["foo"]);
}
TEST_F(MetricsRegistryCounterTest, TestCountAddOutOfRange)
{
  reg->Increment("foo", 5);
  reg->Increment("foo", UINT64_MAX);
  auto counters = reg->GetCounters();
  EXPECT_EQ(UINT64_MAX, counters["foo"]);
}

