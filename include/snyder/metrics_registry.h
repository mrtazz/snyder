/**
 * @file snyder.h
 * @brief metrics library for C++11
 * @author Daniel Schauenberg <d@unwiredcouch.com>
 * @version
 */

#ifndef INCLUDE_SNYDER_H_
#define INCLUDE_SNYDER_H_

#include <string>
#include <map>
#include <mutex>

#include "snyder/version.h"

namespace Snyder {

  /**
   * @brief namespace level variable to get the version of snyder the code was
   * built with. The version comes from the generated version.h and is built
   * in Makefile.am from `git describe --tags --always --dirty`
   */
  static const std::string VERSION = SNYDER_VERSION;

  /**
   * @brief type definition for generic metrics store
   */
  typedef std::map<std::string, uint64_t> MetricsStore;
  /**
   * @brief type definition for the data type returned by Snapshot()
   */
  typedef struct MetricsSnapshot {
    /**
     * @brief stores a copy of the counters MetricsStore
     */
    MetricsStore counters;
    /**
     * @brief stores a copy of the gauges MetricsStore
     */
    MetricsStore gauges;
  } MetricsSnapshot;

  /**
   * @brief central metrics registry. You can have multiple of those and each
   * instance will have their own set of metrics.
   */
  class MetricsRegistry
  {
    public:
      MetricsRegistry();
      ~MetricsRegistry();

      // generic methods
      void Reset();
      MetricsSnapshot Snapshot();

      // Metrics tracking and retrieval methods
      // Counters
      size_t Increment(const std::string& name);
      size_t Increment(const std::string& name, uint64_t count);

      MetricsStore GetCounters();
      void ResetCounters();

      // Gauges
      size_t Gauge(const std::string& name, uint64_t value);

      MetricsStore GetGauges();
      void ResetGauges();

    private:
      MetricsRegistry(const MetricsRegistry&) = delete;
      MetricsRegistry(MetricsRegistry&&) = delete;
      MetricsStore counterRegistry;
      MetricsStore gaugesRegistry;
      std::mutex counterMutex;
      std::mutex gaugesMutex;
  };

}

#endif  // INCLUDE_SNYDER_H_
