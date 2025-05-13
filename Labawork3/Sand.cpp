#include "Sand.h"
#include <fstream>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <sstream>
#include <iomanip>

SandSim::SandSim(dimension_t rows, dimension_t cols)
    : height(rows), width(cols),
    grid(rows, std::vector<int>(cols, 0)),
    next_grid(rows, std::vector<int>(cols, 0)) {
}

bool SandSim::is_within_bounds(int y, int x) const {
    return y >= 0 && x >= 0 && static_cast<dimension_t>(y) < height && static_cast<dimension_t>(x) < width;
}

bool SandSim::load(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile) return false;

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        dimension_t x, y;
        uint64_t grains;
        if (!(iss >> x >> y >> grains)) continue;
        if (is_within_bounds(y, x)) {
            grid[y][x] += static_cast<int>(grains);
        }
    }

    return true;
}

bool SandSim::perform_step() {
    bool unchanged = true;
    next_grid = grid;

    for (dimension_t y = 0; y < height; ++y) {
        for (dimension_t x = 0; x < width; ++x) {
            int grain_count = grid[y][x];
            if (grain_count >= 4) {
                unchanged = false;
                next_grid[y][x] -= 4;
                if (is_within_bounds(y - 1, x)) next_grid[y - 1][x] += 1;
                if (is_within_bounds(y + 1, x)) next_grid[y + 1][x] += 1;
                if (is_within_bounds(y, x - 1)) next_grid[y][x - 1] += 1;
                if (is_within_bounds(y, x + 1)) next_grid[y][x + 1] += 1;
            }
        }
    }

    grid.swap(next_grid);
    return unchanged;
}

bool SandSim::save_to_bmp(std::size_t step_number, const std::string& directory) const {
    namespace fs = std::filesystem;
    if (!fs::is_directory(fs::path(directory))) return false;

    const int scale = 10; // масштаб 1 €чейка = 10x10 пикселей
    int32_t image_width = static_cast<int32_t>(width * scale);
    int32_t image_height = static_cast<int32_t>(height * scale);
    int padding = (4 - (image_width * 3) % 4) % 4;
    int row_size = image_width * 3 + padding;
    int pixel_array_size = row_size * image_height;
    int file_size = 54 + pixel_array_size;

    std::string dir = directory;
    if (!dir.empty() && dir.back() != '/' && dir.back() != '\\')
        dir += '/';

    std::ostringstream ss;
    ss << std::setw(6) << std::setfill('0') << step_number;
    std::string filename = dir + "frame_" + ss.str() + ".bmp";

    uint8_t header[54] = {};
    std::memcpy(header, "BM", 2);
    std::memcpy(header + 2, &file_size, 4);
    int data_offset = 54;
    std::memcpy(header + 10, &data_offset, 4);
    int header_size = 40;
    std::memcpy(header + 14, &header_size, 4);
    std::memcpy(header + 18, &image_width, 4);
    std::memcpy(header + 22, &image_height, 4);
    short planes = 1;
    short bpp = 24;
    std::memcpy(header + 26, &planes, 2);
    std::memcpy(header + 28, &bpp, 2);

    std::ofstream bmp_file(filename, std::ios::binary);
    if (!bmp_file) return false;
    bmp_file.write(reinterpret_cast<char*>(header), sizeof(header));

    // ѕишем изображение снизу вверх
    for (int row = static_cast<int>(height) - 1; row >= 0; --row) {
        for (int sy = 0; sy < scale; ++sy) {
            for (dimension_t col = 0; col < width; ++col) {
                int val = grid[row][col];
                uint8_t r = 255, g = 255, b = 255;

                if (val == 1) { r = 0; g = 255; b = 0; }        // зелЄный
                else if (val == 2) { r = 128; g = 0; b = 128; } // фиолетовый
                else if (val == 3) { r = 255; g = 255; b = 0; } // жЄлтый
                else if (val > 3) { r = 0; g = 0; b = 0; }      // чЄрный

                for (int sx = 0; sx < scale; ++sx) {
                    bmp_file.put(b).put(g).put(r);
                }
            }
            for (int p = 0; p < padding; ++p) bmp_file.put(0);
        }
    }

    return true;
}
