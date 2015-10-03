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
TEST_F(MetricsRegistryTest, TestSnapshot)
{
  auto reg = new Snyder::MetricsRegistry();
  reg->Increment("foo");
  reg->Gauge("foo", 2);
  auto snapshot = reg->Snapshot();
  EXPECT_EQ(1, snapshot.counters["foo"]);
  EXPECT_EQ(2, snapshot.gauges["foo"]);
}
TEST_F(MetricsRegistryTest, TestResetMetrics)
{
  auto reg = new Snyder::MetricsRegistry();
  reg->Increment("foo");
  reg->Gauge("foo", 2);
  auto snapshot = reg->Snapshot();
  EXPECT_EQ(1, snapshot.counters["foo"]);
  EXPECT_EQ(2, snapshot.gauges["foo"]);
  reg->Reset();
  auto snapshot2 = reg->Snapshot();
  EXPECT_EQ(0, snapshot2.counters["foo"]);
  EXPECT_EQ(0, snapshot2.gauges["foo"]);
}
