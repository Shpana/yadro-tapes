#ifndef YADRO_TAPES_SLEEPING_WORKLOAD_HPP
#define YADRO_TAPES_SLEEPING_WORKLOAD_HPP

#include "workload.hpp"

#include <chrono>
#include <thread>

struct SleepingWorkloadSpec {
  std::chrono::milliseconds reading_delay{0};
  std::chrono::milliseconds writing_delay{0};
  std::chrono::milliseconds moving_delay{0};

  SleepingWorkloadSpec() = default;
};

class SleepingWorkload : public Workload {
public:
  SleepingWorkload(SleepingWorkloadSpec spec)
      : _spec(spec) {}

  void trigger_read() override {
    std::this_thread::sleep_for(_spec.reading_delay);
  }

  void trigger_write() override {
    std::this_thread::sleep_for(_spec.writing_delay);
  }

  void trigger_movement() override {
    std::this_thread::sleep_for(_spec.moving_delay);
  }

private:
  SleepingWorkloadSpec _spec;
};

#endif// YADRO_TAPES_SLEEPING_WORKLOAD_HPP
