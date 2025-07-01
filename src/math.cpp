#include <cmath>
#include <iostream>   // for std::cerr
#include <stdexcept>
#include "math.hpp"

double lambert_wm1(double x, double tol, int max_iter) {
    // Corless, R.M., Gonnet, G.H., Hare, D.E.G. et al. On the LambertW function.
    // Adv Comput Math 5, 329–359 (1996). https://doi.org/10.1007/BF02124750 

    if (x >= 0 || x < -1.0 / std::exp(1.0)) {
        std::cerr << "Warning in function '" << __func__
            << "': lambert_wm1 is only defined for -1/e < x < 0\n";
        return std::numeric_limits<double>::quiet_NaN();
    }

    double L1 = std::log(-x);
    double L2 = std::log(-L1);
    double w = L1 - L2 + (L2 / L1);

    for (int i = 0; i < max_iter; ++i) {
        double ew = std::exp(w);
        double w_ew = w * ew;
        double diff = (w_ew - x) / (ew * (w + 1) - ((w + 2) * (w_ew - x)) / (2 * w + 2));
        w -= diff;
        if (std::abs(diff) < tol) {
            return w;
        }
    }

    std::cerr << "Warning in function '" << __func__
        << "': lambert_wm1 did not converge.\n";
    return std::numeric_limits<double>::quiet_NaN();
}

double Interp1d(const std::vector<double>& x_coords, const std::vector<double>& y_coords,
                double x, size_t* insertion_index) {
    if (x_coords.size() != y_coords.size() || x_coords.empty()) {
        throw std::invalid_argument("Input vectors must be non-empty and have the same size.");
    }
    
    if (x_coords.size() == 1) {
        if (insertion_index) {
            // Insert after if x is greater, otherwise before.
            *insertion_index = (x > x_coords[0] ? 1 : 0);
        }
        return y_coords[0];
    }

    // --- Handle edge cases ---
    if (x_coords.back() > x_coords.front()) { // ascending order
        if (x >= x_coords.back()) {
            if (insertion_index) *insertion_index = x_coords.size();
            return y_coords.back();
        }
        if (x <= x_coords.front()) {
            if (insertion_index) *insertion_index = 0;
            return y_coords.front();
        }
    } else { // descending order or all same
        if (x <= x_coords.back()) {
            if (insertion_index) *insertion_index = x_coords.size();
            return y_coords.back();
        }
        if (x >= x_coords.front()) {
            if (insertion_index) *insertion_index = 0;
            return y_coords.front();
        }
    }

    // find the two x-coordinates that bracket x using linear scan (may upgrade to
    // binary search later)
    for(int i = 0; i < x_coords.size()-1; ++i) {
        if (x == x_coords[i]) {
            if (insertion_index) *insertion_index = i;
            return y_coords[i];
        }
        if ((x - x_coords[i]) * (x - x_coords[i+1]) < 0) {
            if (insertion_index) *insertion_index = i+1;
            return y_coords[i] + (x - x_coords[i]) * (y_coords[i+1] - y_coords[i])
                / (x_coords[i+1] - x_coords[i]); 
        }
    }

    throw std::runtime_error("Interpolation failed: could not find bracketing interval..");
}

void Interp1dAndInsert(const std::vector<double>& x_coords, std::vector<double>& y_coords, double new_x) {
    size_t insertion_index = 0;
    double new_y = Interp1d(x_coords, y_coords, new_x, &insertion_index);
    y_coords.insert(y_coords.begin() + insertion_index, new_y);
}
