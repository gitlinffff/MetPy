// constants.cpp
#include "constants.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace metpy_constants {
    double Mw;
    double Rd;
    double Rv;
    double Cp_d;
    double Cp_v;
    double Cp_l;
    double Lv;
    double sat_pressure_0c;
    double T0;
    double Ls;
    double Cp_i;
    double zero_degc;
    double epsilon;
    double kappa;

    // Additional constants not in MetPy (for H2O svp formulation in broader range)
    double pr;
    double tr;
    double betal;
    double betas;
    double gammal;
    double gammas;

    void load_constants_from_python() {
        py::object mod = py::module_::import("metpy.constants.nounit");

//        Mw = mod.attr("Mw").attr("magnitude").cast<double>();
//        Rv = mod.attr("Rv").attr("magnitude").cast<double>();
//        Cp_v = mod.attr("Cp_v").attr("magnitude").cast<double>();
//        Cp_l = mod.attr("Cp_l").attr("magnitude").cast<double>();
//        Lv = mod.attr("Lv").attr("magnitude").cast<double>(); 
//        sat_pressure_0c = mod.attr("sat_pressure_0c").cast<double>();
//        T0 = mod.attr("T0").attr("magnitude").cast<double>();


        Mw = mod.attr("Mw").cast<double>();
        Rd = mod.attr("Rd").cast<double>();
        Rv = mod.attr("Rv").cast<double>();
        Cp_d = mod.attr("Cp_d").cast<double>();
        Cp_v = mod.attr("Cp_v").cast<double>();
        Cp_l = mod.attr("Cp_l").cast<double>();
        Lv = mod.attr("Lv").cast<double>(); 
        sat_pressure_0c = mod.attr("sat_pressure_0c").cast<double>();
        T0 = mod.attr("T0").cast<double>();
        Ls = mod.attr("Ls").cast<double>();
        Cp_i = mod.attr("Cp_i").cast<double>();
        zero_degc = mod.attr("zero_degc").cast<double>();
        epsilon = mod.attr("epsilon").cast<double>();
        kappa = mod.attr("kappa").cast<double>();

        // Additional constants not in MetPy (for H2O svp formulation in broader range)
        pr = 611.7;
        tr = 273.16;
        betal = 24.845;
        betas = 22.98;
        gammal = 4.986009;
        gammas = 0.52;
    }
}
