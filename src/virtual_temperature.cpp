#include "virtual_temperature.hpp"
//#include <stdexcept>

double VirtualTemperature(double temperature, double mixing_ratio, double epsilon) {
    return temperature * (mixing_ratio + epsilon) / (epsilon * (1. + mixing_ratio));
}
