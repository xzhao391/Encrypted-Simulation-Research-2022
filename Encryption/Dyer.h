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


//class EXPORT Dyer {
//public:
//    struct PKey {  // Public Key
//        wide_uint_t kappa;
//        wide_uint_t p;
//    };
//
//    //wide_uint_t keygen(int bit_length, int rho, int rho_);
//	Dyer::PKey keygen(int bit_length, int rho, int rho_);
//	wide_uint_t get_prime(int bit_length);
//	wide_uint_t read_prime_from_file(int bit_length);
//    wide_uint_t pgen(int bit_length, int rho_, wide_uint_t p);
//	wide_uint_t encode(wide_double_t x, wide_double_t delta);
//    wide_double_t decode(int m, wide_double_t delta);
//	wide_uint_t get_rand(wide_uint_t min, wide_uint_t max);
//    cipher_text encrypt(wide_uint_t m, PKey key, wide_uint_t modulus);
//	wide_int_t min_residue(const wide_int_t&  a, const wide_int_t& m);
//    int decrypt(cipher_text c, PKey key);
//    cipher_text enc(wide_double_t x, PKey key, wide_uint_t modulus, wide_double_t delta);	
//    wide_double_t dec(cipher_text c, PKey key, wide_double_t delta);
//    cipher_text add(cipher_text c1, cipher_text c2, wide_uint_t modulus);
//    cipher_text mul(cipher_text c1, cipher_text c2, wide_uint_t modulus); 
//};

#endif