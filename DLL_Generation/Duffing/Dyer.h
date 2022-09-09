#ifndef DYER
#define DYER
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include "wide_data.h"

#include <string>
#include <iostream>
#include <fstream>

class Dyer
{
public:
    void duffing(double input, double x_in, double x_dot_in, double x_3_in, double Ts,
                 double d, double a, double B,
                 int bit_length, int rho, int rho_, double delta, double arr[]);
};
#endif
