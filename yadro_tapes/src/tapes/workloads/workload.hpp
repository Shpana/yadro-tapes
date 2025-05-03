#ifndef YADRO_TAPES_WORKLOAD_HPP
#define YADRO_TAPES_WORKLOAD_HPP

class Workload {
public:
  virtual ~Workload() = default;

  virtual void trigger_read() = 0;
  virtual void trigger_write() = 0;
  virtual void trigger_movement() = 0;
};

#endif// YADRO_TAPES_WORKLOAD_HPP
