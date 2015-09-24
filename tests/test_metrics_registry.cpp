#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

#include "snyder/metrics_registry.h"

// The fixture for testing class Foo.
class MetricsRegistryTest : public ::testing::Test
{
 protected:

    MetricsRegistryTest()
    {
    }

    virtual ~MetricsRegistryTest()
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
TEST_F(MetricsRegistryTest, TestAddSimpleCounter)
{
  auto reg = new Snyder::MetricsRegistry();
  reg->Increment("foo");
  auto counters = reg->GetCounters();

  EXPECT_EQ(1, counters["foo"]);
}
TEST_F(MetricsRegistryTest, TestAddCounterWithSpecifiedValue)
{
  auto reg = new Snyder::MetricsRegistry();
  reg->Increment("foo", 5);
  auto counters = reg->GetCounters();

  EXPECT_EQ(5, counters["foo"]);
}
TEST_F(MetricsRegistryTest, TestIncrementExistingCounter)
{
  auto reg = new Snyder::MetricsRegistry();
  reg->Increment("foo");
  reg->Increment("foo", 5);
  auto counters = reg->GetCounters();

  EXPECT_EQ(6, counters["foo"]);
}

