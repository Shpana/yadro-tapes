#ifndef YADRO_TAPES_CONFIGS_HPP
#define YADRO_TAPES_CONFIGS_HPP

#include "yaml-cpp/yaml.h"

#include "tapes/workloads/delaying_workload.hpp"

#include <chrono>
#include <filesystem>

auto LoadSleepingWorkloadSpec(const std::filesystem::path& filepath)
    -> DelayingWorkload::Spec {
  auto config = YAML::LoadFile(filepath.string());
  if (!config["sleeping-workload"])
    return {};
  auto workload_config = config["sleeping-workload"];

  DelayingWorkload::Spec spec{};
  if (workload_config["reading-delay"])
    spec.reading_delay = static_cast<std::chrono::milliseconds>(
        workload_config["reading-delay"].as<size_t>());
  if (workload_config["writing-delay"])
    spec.writing_delay = static_cast<std::chrono::milliseconds>(
        workload_config["writing-delay"].as<size_t>());
  if (workload_config["moving-delay"])
    spec.moving_delay = static_cast<std::chrono::milliseconds>(
        workload_config["moving-delay"].as<size_t>());
  return spec;
}

#endif// YADRO_TAPES_CONFIGS_HPP
