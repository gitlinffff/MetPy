#ifndef MATH_HPP
#define MATH_HPP

double lambert_wm1(double x, double tol = 1e-10, int max_iter = 100);

double Interp1d(const std::vector<double>& x_coords, const std::vector<double>& y_coords,
                double x, size_t* insertion_index = nullptr);
void Interp1dAndInsert(const std::vector<double>& x_coords, std::vector<double>& y_coords, double new_x);
#endif // MATH_HPP

