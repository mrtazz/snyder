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
  this->Increment(name, 1);
  return 0;
}
size_t MetricsRegistry::Increment(const std::string& name, uint64_t count) {
  std::lock_guard<std::mutex> lock(counterMutex);
  counterRegistry[name] += count;
  return 0;
}

size_t MetricsRegistry::Gauge(const std::string& name, uint64_t value) {
  std::lock_guard<std::mutex> lock(gaugesMutex);
  gaugesRegistry[name] = value;
  return 0;
}
