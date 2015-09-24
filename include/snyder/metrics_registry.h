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

namespace Snyder {

  typedef std::map<std::string, uint64_t> MetricsStore;

  class MetricsRegistry
  {
    public:
      MetricsRegistry();
      ~MetricsRegistry();

      // Metrics tracking and retrieval methods
      // Counters
      size_t Increment(const std::string& name);
      size_t Increment(const std::string& name, uint64_t count);

      const MetricsStore& GetCounters() const {return counterRegistry;}

      // Gauges
      size_t Gauge(const std::string& name, uint64_t value);

      const MetricsStore& GetGauges() const {return gaugesRegistry;}

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
