#include <iostream>
#include <cstring>
#include <cstdlib>
#include "Sand.h"
#include <filesystem>


using std::cout;
using std::endl;

bool strings_equal(const char* s1, const char* s2) {
    while (*s1 && *s2) {
        if (*s1++ != *s2++) return false;
    }
    return *s1 == *s2;
}

struct Config {
    dimension_t h = 0, w = 0;
    const char* input = nullptr;
    const char* output = nullptr;
    unsigned long long max_iters = 1, save_rate = 1;
};

bool parse_arguments(int argc, char* argv[], Config& cfg) {
    for (int idx = 1; idx < argc; ++idx) {
        if (argv[idx][0] == '-') {
            const char* arg = argv[idx];
            if (idx + 1 >= argc) return false;
            const char* next = argv[idx + 1];

            if (arg[1] == '-') {
                if (strings_equal(arg, "--length")) cfg.h = std::strtoul(next, nullptr, 10);
                else if (strings_equal(arg, "--width")) cfg.w = std::strtoul(next, nullptr, 10);
                else if (strings_equal(arg, "--input")) cfg.input = next;
                else if (strings_equal(arg, "--output")) cfg.output = next;
                else if (strings_equal(arg, "--max-iter")) cfg.max_iters = std::strtoull(next, nullptr, 10);
                else if (strings_equal(arg, "--freq")) cfg.save_rate = std::strtoull(next, nullptr, 10);
                else return false;
            }
            else {
                switch (arg[1]) {
                case 'l': cfg.h = std::strtoul(next, nullptr, 10); break;
                case 'w': cfg.w = std::strtoul(next, nullptr, 10); break;
                case 'i': cfg.input = next; break;
                case 'o': cfg.output = next; break;
                case 'm': cfg.max_iters = std::strtoull(next, nullptr, 10); break;
                case 'f': cfg.save_rate = std::strtoull(next, nullptr, 10); break;
                default: return false;
                }
            }
            ++idx;
        }
    }
    return true;
}

bool export_image(unsigned long long step, const Config& cfg, SandSim& sim) {
    if (sim.save_to_bmp(step, cfg.output)) {
        cout << "Saved iteration " << step << " to \"" << cfg.output << "\"\n";
        return true;
    }
    else {
        cout << "Failed to save BMP to folder \"" << cfg.output << "\"\n";
        cout << "Ensure the path ends with '/' character.\n";
        return false;
    }
}

int main(int argc, char* argv[]) {
    Config cfg;
    if (!parse_arguments(argc, argv, cfg)) {
        cout << "Error parsing arguments.\n";
        return 1;
    }

    cout << "=== Configuration ===\n";
    cout << "Height: " << cfg.h << "\nWidth: " << cfg.w << "\n";
    cout << "Input: " << (cfg.input ? cfg.input : "none") << "\n";
    cout << "Output: " << (cfg.output ? cfg.output : "none") << "\n";
    cout << "Max iterations: " << cfg.max_iters << "\nFrequency: " << cfg.save_rate << "\n\n";

    if (cfg.h == 0 || cfg.w == 0 || cfg.output == nullptr) {
        cout << "Invalid configuration: dimensions or output folder not set.\n";
        return 2;
    }

    SandSim model(cfg.h, cfg.w);
    if (cfg.input && !model.load(cfg.input)) {
        cout << "Could not open input file \"" << cfg.input << "\"\n";
        return 3;
    }

    if (cfg.save_rate > 0) {
        if (!export_image(0, cfg, model)) return 4;
        for (unsigned long long i = 1; i <= cfg.max_iters && !model.perform_step(); ++i) {
            if (i % cfg.save_rate == 0) {
                if (!export_image(i, cfg, model)) return 4;
            }
        }
    }
    else {
        unsigned long long step = 1;
        while (step <= cfg.max_iters && !model.perform_step()) ++step;
        if (!export_image(step, cfg, model)) return 4;
    }

    return 0;
}
