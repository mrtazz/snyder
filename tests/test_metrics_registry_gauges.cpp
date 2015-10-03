#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

#include "snyder/metrics_registry.h"

// The fixture for testing class Foo.
class MetricsRegistryGaugesTest : public ::testing::Test
{
 protected:
    Snyder::MetricsRegistry* reg;

    MetricsRegistryGaugesTest()
    {
    }

    virtual ~MetricsRegistryGaugesTest()
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
TEST_F(MetricsRegistryGaugesTest, TestAddSimpleGauge)
{
  reg->Gauge("foo", 1);
  auto gauges = reg->GetGauges();

  EXPECT_EQ(1, gauges["foo"]);
}
TEST_F(MetricsRegistryGaugesTest, TestChangeGauge)
{
  reg->Gauge("foo", 1);
  reg->Gauge("foo", 4);
  auto gauges = reg->GetGauges();

  EXPECT_EQ(4, gauges["foo"]);
}
TEST_F(MetricsRegistryGaugesTest, TestClearGauges)
{
  reg->Gauge("foo", 1);
  reg->Gauge("foo", 4);
  auto gauges = reg->GetGauges();
  EXPECT_EQ(4, gauges["foo"]);
  reg->ResetGauges();
  auto gauges2 = reg->GetGauges();
  EXPECT_EQ(0, gauges2["foo"]);
}
