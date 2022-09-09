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
    //struct point_group1 {
    //	double x[2];
    //};

    //wide_uint_t encode(wide_double_t x, wide_double_t delta);
    void control(double xm, double dxm, double ddxm, double xs, double dxs,
                 double ddxs, double mms, double kms, double bms, double um, double us, double mm, double ms,
                 int bit_length, int rho, int rho_, double delta, double arr[]);
};
#endif
