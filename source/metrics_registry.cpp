/**
 * @file snyder.cpp
 * @brief implementation of the MetricsRegistry
 * @author Daniel Schauenberg <d@unwiredcouch.com>
 */

#include "snyder/metrics_registry.h"

using namespace Snyder;

MetricsRegistry::MetricsRegistry() : counterMutex(), gaugesMutex() {
}
MetricsRegistry::~MetricsRegistry() {
}

size_t MetricsRegistry::Increment(const std::string& name) {

  return 0;
}
size_t MetricsRegistry::Increment(const std::string& name, uint64_t count) {

  return 0;
}
