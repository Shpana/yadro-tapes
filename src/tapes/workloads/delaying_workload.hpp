#ifndef YADRO_TAPES_DELAYING_WORKLOAD_HPP
#define YADRO_TAPES_DELAYING_WORKLOAD_HPP

#include "workload.hpp"

#include <chrono>
#include <thread>

class DelayingWorkload : public Workload {
public:
  struct Spec {
    std::chrono::milliseconds reading_delay{0};
    std::chrono::milliseconds writing_delay{0};
    std::chrono::milliseconds moving_delay{0};
  };

public:
  DelayingWorkload() = default;
  DelayingWorkload(const Spec& spec) : spec_(spec) {}

  auto TriggerRead() -> void override { Delay(spec_.reading_delay); }
  auto TriggerWrite() -> void override { Delay(spec_.writing_delay); }
  auto TriggerMovement() -> void override { Delay(spec_.moving_delay); }

private:
  auto Delay(std::chrono::milliseconds ms) -> void { std::this_thread::sleep_for(ms); }

private:
  Spec spec_{};
};

#endif// YADRO_TAPES_DELAYING_WORKLOAD_HPP
