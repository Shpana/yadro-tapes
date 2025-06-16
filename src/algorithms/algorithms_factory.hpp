#ifndef YADRO_TAPES_ALGORITHMS_FACTORY_HPP
#define YADRO_TAPES_ALGORITHMS_FACTORY_HPP

#include "bubble_sort_algorithm.hpp"
#include "merge_sort_algorithm.hpp"

#include <filesystem>

auto CreateBubbleSortAlgorithm(
    std::filesystem::path&& input_filepath,
    std::filesystem::path&& output_filepath, std::size_t size)
    -> std::unique_ptr<BubbleSortAlgorithm>;

auto CreateBubbleSortAlgorithm(
    TapePtr&& input_tape,
    TapePtr&& output_tape)
    -> std::unique_ptr<BubbleSortAlgorithm>;

auto CreateMergeSortAlgorithm(
    std::filesystem::path&& input_filepath,
    std::filesystem::path&& output_filepath,
    std::size_t size, std::size_t memory_limit)
    -> std::unique_ptr<MergeSortAlgorithm>;

auto CreateMergeSortAlgorithm(
    TapePtr&& input_tape,
    TapePtr&& output_tape,
    std::array<TapePtr, 2>&& extra_tapes,
    std::size_t memory_limit)
    -> std::unique_ptr<MergeSortAlgorithm>;

#endif// YADRO_TAPES_ALGORITHMS_FACTORY_HPP
