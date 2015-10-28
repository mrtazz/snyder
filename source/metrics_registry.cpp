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

/**
 * @brief method to increment a metric by 1
 *
 * @param name the name of the counter to increment
 *
 * @return int 0 on success
 */
int MetricsRegistry::Increment(const std::string& name) {
  return this->Increment(name, 1);
}

/**
 * @brief method to increment a metric by a given count
 *
 * @param name the name of the counter to increment
 * @param count integer to increment the counter by
 *
 * @return int 0 on success
 */
int MetricsRegistry::Increment(const std::string& name, uint64_t count) {
    std::lock_guard<std::mutex> lock(counterMutex);
    uint64_t value = counterRegistry[name];
    // detect overflow in addition and set value to MAX
    if (count > 0 && value > (UINT64_MAX - count)) {
      counterRegistry[name] = UINT64_MAX;
    } else {
      counterRegistry[name] += count;
    }
    return 0;
}

/**
 * @brief method to decrement a metric by 1. If the result would be negative,
 * the counter is set to 0.
 *
 * @param name the name of the counter to decrement
 *
 * @return int 0 on success, 1 if count is out of range
 */
int MetricsRegistry::Decrement(const std::string& name) {
  return this->Decrement(name, 1);
}

/**
 * @brief method to decrement a metric by a given count. If the result would
 * be negative, the counter is set to 0.
 *
 * @param name the name of the counter to increment
 * @param count integer to decrement the counter by
 *
 * @return int 0 on success
 */
int MetricsRegistry::Decrement(const std::string& name, uint64_t count) {
  std::lock_guard<std::mutex> lock(counterMutex);
  uint64_t value = counterRegistry[name];
  if (value < count) {
    counterRegistry[name] = 0;
  } else {
    counterRegistry[name] = (value - count);
  }
  return 0;
}

/**
 * @brief method to record a gauge value
 *
 * @param name the name of the gauge to record
 * @param value the value of the gauge to record
 *
 * @return int 0 on success, 1 if value is out of range
 */
int MetricsRegistry::Gauge(const std::string& name, uint64_t value) {
  std::lock_guard<std::mutex> lock(gaugesMutex);
  gaugesRegistry[name] = value;
  return 0;
}


/**
* @brief method to get the MetricsStore backing counters. This will
* return by value thus locking the mutex for the duration it takes to
* copy the data structure.
*
* @return MetricsStore
*/
MetricsStore MetricsRegistry::GetCounters() {
  std::lock_guard<std::mutex> lock(counterMutex);
  return counterRegistry;
}

/**
* @brief method to get the MetricsStore backing gauges. This will return
* by value thus locking the mutex for the duration it takes to copy the
* data structure.
*
* @return MetricsStore
*/
MetricsStore MetricsRegistry::GetGauges() {
  std::lock_guard<std::mutex> lock(gaugesMutex);
  return gaugesRegistry;
}

/**
 * @brief reset/clear all metrics
 *
 * @return void
 */
void MetricsRegistry::Reset() {
  this->ResetCounters();
  this->ResetGauges();
}

/**
 * @brief get a snapshot of the current state of metrics
 *
 * @return MetricsSnapshot
 */
MetricsSnapshot MetricsRegistry::Snapshot() {
  MetricsSnapshot ret;

  ret.counters = this->GetCounters();
  ret.gauges = this->GetGauges();

  return ret;
}

/**
 * @brief reset/clear all counters
 *
 * @return void
 */
void MetricsRegistry::ResetCounters() {
  std::lock_guard<std::mutex> lock(counterMutex);
  counterRegistry.clear();
}

/**
 * @brief reset/clear all gauges
 *
 * @return void
 */
void MetricsRegistry::ResetGauges() {
  std::lock_guard<std::mutex> lock(gaugesMutex);
  gaugesRegistry.clear();
}
