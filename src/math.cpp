#include "math.hpp"

// put function definitions here:
int add (int x, int y) {
  return x + y;
}



#ifndef ARDUINO
#include <cmath>

// New function: apply a gain to each sample in-place, rounding to nearest int
void apply_gain(std::vector<int>& buffer, double gain) {
    for (size_t i = 0; i < buffer.size(); ++i) {
        double scaled = static_cast<double>(buffer[i]) * gain;
        buffer[i] = static_cast<int>(std::lround(scaled));
    }
}
#endif