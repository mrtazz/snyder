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

    MetricsRegistryGaugesTest()
    {
    }

    virtual ~MetricsRegistryGaugesTest()
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
TEST_F(MetricsRegistryGaugesTest, TestAddSimpleGauge)
{
  auto reg = new Snyder::MetricsRegistry();
  reg->Gauge("foo", 1);
  auto gauges = reg->GetGauges();

  EXPECT_EQ(1, gauges["foo"]);
}
