#ifndef YADRO_TAPES_WORKLOAD_HPP
#define YADRO_TAPES_WORKLOAD_HPP

class Workload {
public:
  virtual ~Workload() = default;

  virtual auto TriggerRead() -> void = 0;
  virtual auto TriggerWrite() -> void = 0;
  virtual auto TriggerMovement() -> void = 0;
};

#endif// YADRO_TAPES_WORKLOAD_HPP
