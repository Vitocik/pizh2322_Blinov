#pragma once
#include <string>
#include <vector>
#include <cstddef>

using dimension_t = std::size_t;

class SandSim {
public:
    SandSim(dimension_t rows, dimension_t cols);
    bool load(const std::string& filename);
    bool save_to_bmp(std::size_t step_number, const std::string& directory) const;
    bool perform_step(); // returns true if stable

private:
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<int>> next_grid;
    dimension_t height, width;

    bool is_within_bounds(int y, int x) const;
};
