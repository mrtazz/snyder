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

    MetricsRegistryCounterTest()
    {
    }

    virtual ~MetricsRegistryCounterTest()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

};

// Tests that a simple mustache tag is replaced
TEST_F(MetricsRegistryCounterTest, TestAddSimpleCounter)
{
  auto reg = new Snyder::MetricsRegistry();
  reg->Increment("foo");
  auto counters = reg->GetCounters();

  EXPECT_EQ(1, counters["foo"]);
}
TEST_F(MetricsRegistryCounterTest, TestAddCounterWithSpecifiedValue)
{
  auto reg = new Snyder::MetricsRegistry();
  reg->Increment("foo", 5);
  auto counters = reg->GetCounters();

  EXPECT_EQ(5, counters["foo"]);
}
TEST_F(MetricsRegistryCounterTest, TestIncrementExistingCounter)
{
  auto reg = new Snyder::MetricsRegistry();
  reg->Increment("foo");
  reg->Increment("foo", 5);
  auto counters = reg->GetCounters();

  EXPECT_EQ(6, counters["foo"]);
}
TEST_F(MetricsRegistryCounterTest, TestClearCounters)
{
  auto reg = new Snyder::MetricsRegistry();
  reg->Increment("foo");
  auto counters = reg->GetCounters();
  EXPECT_EQ(1, counters["foo"]);
  reg->ResetCounters();
  auto counters2 = reg->GetCounters();
  EXPECT_EQ(0, counters2["foo"]);
}

